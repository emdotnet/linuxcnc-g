#!/bin/bash

p=$(dirname `realpath $0`)
source ${p}/activate-linuxcnc.sh

# When running with "-v", the test itself runs in a pipeline with tee, and
# without pipefail we get the exit value from tee instead of from the test.
set -o pipefail

# The linuxcnc starter script sometimes tries to display X windows if
# DISPLAY is set.  We never want that while running tests, so unset it.
unset DISPLAY

# Some of our tests emit locale-sensitive strings, so reset the locale
# to a sane default.
export LC_ALL=C


case "$0" in
	*/*) MYDIR="${0%/*}" ;;
	*) MYDIR="`type -path $0`"; MYDIR="${MYDIR%/*}"
esac
MYDIR=$(cd $MYDIR; pwd);
TOPDIR=$(cd $MYDIR/..; pwd)

#prefix=@prefix@
#if test @RUN_IN_PLACE@ = yes; then
#    . $TOPDIR/scripts/rip-environment >&/dev/null
#    export HEADERS=@EMC2_HOME@/include
#    export LIBDIR=${TOPDIR}/lib
#    export REALTIME=realtime
#else
#    # Set $EMC2_HOME to $prefix for tests that depend on it
#    export SYSTEM_BUILD=1
#    export EMC2_HOME=@EMC2_HOME@
#    export HEADERS=@includedir@/linuxcnc
#    export LIBDIR=@EMC2_HOME@/lib
#    export LINUXCNC_EMCSH=@WISH@
#    export REALTIME=/etc/init.d/realtime
#    export SUDO=sudo
#fi
#export PYTHON_CPPFLAGS="@PYTHON_CPPFLAGS@"
#export PYTHON_EXTRA_LIBS="@PYTHON_EXTRA_LIBS@"
#export PYTHON_EXTRA_LDFLAGS="@PYTHON_EXTRA_LDFLAGS@"
#export PYTHON_LIBS="@PYTHON_EXTRA_LIBS@"

export RUNTESTS="$(readlink -f $0)"

NUM=0
FAIL=0; FAIL_NAMES=""
XFAIL=0
VERBOSE=0

clean () {
    find $* \( -name "stderr" -or -name "result" \
	-or -name "*.var" -or -name "*.var.bak" \) \
	-print0 | xargs -0 rm -f
}

run_shell_script () {
    testname=$(basename $1)
    testdir=$(dirname $1)

    pushd $testdir > /dev/null
    if [ $VERBOSE -eq 1 ]; then
        (bash -x $testname | tee result) 3>&1 1>&2 2>&3 | tee stderr
    else
        bash -x $testname > result 2> stderr
    fi
    exitcode=$?
    popd > /dev/null
    return $exitcode
}

run_executable () {
    testname=$(basename $1)
    testdir=$(dirname $1)

    pushd $testdir > /dev/null
    if [ $VERBOSE -eq 1 ]; then
        (./$testname | tee result) 3>&1 1>&2 2>&3 | tee stderr
    else
        ./$testname > result 2> stderr
    fi
    exitcode=$?
    popd > /dev/null
    return $exitcode
}

run_without_overruns () {
    testname=$(basename $1)
    testdir=$(dirname $1)
    for i in $(seq 10); do
        if [ $i != 1 ]; then echo "--- $testdir: overrun detected in sampler, re-running test" 1>&2 ; fi

        pushd $testdir > /dev/null
        if [ $VERBOSE -eq 1 ]; then
            (halrun -f $testname | tee result) 3>&1 1>&2 2>&3 | tee stderr
        else
            halrun -f $testname > result 2> stderr
        fi
        exitcode=$?
        popd > /dev/null

        if ! grep -q '^overrun$' $testdir/result; then return $exitcode; fi
    done
    echo "--- $testdir: $i overruns detected, giving up" 1>&2
    return 1
}

run_test() {
    testname=$1
    case $testname in
        *.hal) run_without_overruns $testname ;;
        *.sh) run_shell_script $testname ;;
        *) run_executable $testname ;;
    esac
}

TMPDIR=`mktemp -d /tmp/runtest.XXXXXX`
trap "rm -rf $TMPDIR" 0 1 2 3 9 15


run_tests () {
    find $* -name test.hal -or -name test.sh -or -name test \
	| sort > $TMPDIR/alltests

    while read testname; do
	testdir=$(dirname $testname)
	if [ -e $testdir/skip ]; then
	    if ! [ -x $testdir/skip ] || ! $testdir/skip; then
		echo "Skipping test: $testdir" 1>&2
		continue
	    fi
	fi
	NUM=$(($NUM+1))
	echo "Running test: $testdir" 1>&2
        if test -n "$SYSTEM_BUILD"; then
            # Tell `halcompile` where to install comps
            USER_MODULE_DIR=$(readlink -f $testdir) \
                PATH=$(readlink -f $testdir):$PATH \
                run_test $testname
        else
            PATH=$(readlink -f $testdir):$PATH \
            run_test $testname
        fi
	exitcode=$?
	if [ $exitcode -ne 0 ]; then
	    reason="test run exited with $exitcode"
	else
	    if [ -e $testdir/checkresult ]; then
		$testdir/checkresult $testdir/result
		exitcode=$?
		reason="checkresult exited with $exitcode"
	    elif [ -f $testdir/expected ]; then
		cmp -s $testdir/expected $testdir/result
		exitcode=$?
		reason="result differed from expected"
		if [ $exitcode -ne 0 ]; then
		    diff -u $testdir/expected $testdir/result > $TMPDIR/diff
		    SIZE=$(wc -l < $TMPDIR/diff)
		    if [ $SIZE -lt 40 ]; then
			cat $TMPDIR/diff
		    else
			OMIT=$((SIZE-40))
			head -40 $TMPDIR/diff
			echo "($OMIT more lines omitted)"
		    fi
		fi
	    else
		exitcode=1
		reason="Neither expected nor checkresult existed"
	    fi
	fi
	if [ $exitcode -ne 0 ]; then
	    echo "*** $testdir: XFAIL: $reason"
            if test $PRINT = 1; then
                echo "************** result:"
                tail -500 $testdir/result | sed 's/^/        /'
                echo "************** stderr:"
                tail -500 $testdir/stderr | sed 's/^/        /'
                echo "**************"
            fi
	    if [ -f $testdir/xfail ]; then
		XFAIL=$(($XFAIL+1))
		if [ $NOCLEAN -eq 0 ]; then
		    rm -f $testdir/stderr $testdir/result \
			$testdir/*.var $testdir/*.var.bak
		fi
	    else
		FAIL=$(($FAIL+1))
		FAIL_NAMES="$FAIL_NAMES
	$testdir"
	    fi
            if test $STOP = 1; then
	        break
	    fi
	else
	    if [ -f $testdir/xfail ]; then
		echo "*** $testdir: XPASS: Passed, but was expected to fail"
	    else
		if [ $NOCLEAN -eq 0 ]; then
		    rm -f $testdir/stderr $testdir/result \
			$testdir/*.var $testdir/*.var.bak
		fi
	    fi
	fi
    done < $TMPDIR/alltests

    SUCC=$((NUM-FAIL-XFAIL))
    echo "Runtest: $NUM tests run, $SUCC successful, $FAIL failed + $XFAIL expected"
    if [ $FAIL -ne 0 ]; then
	echo "Failed: $FAIL_NAMES"
	exit 1;
    else
	exit 0;
    fi
}

usage () {
    P=${0##*/}
    cat <<EOF
$P: Run HAL test suite items

Usage:
    $P [-n] [-s] [-p] tests
	Run tests.  With '-n', do not remove temporary files for successful
	tests.  With '-s', stop after any failed test.  With '-p', print
        stderr and result files.

    $P -c tests
	Remove temporary files from an earlier test run.

    $P -v
        Show stdout and stderr (normally it's hidden).
EOF
}

CLEAN_ONLY=0
NOCLEAN=0
STOP=0
PRINT=0
while getopts cnvsph opt; do
    case "$opt" in
    c) CLEAN_ONLY=1 ;;
    n) NOCLEAN=1 ;;
    v) VERBOSE=1 ;;
    s) STOP=1 ;;
    p) PRINT=1 ;;
    h|?) usage; exit 0 ;;
    *) usage; exit 1 ;;
    esac
done
shift $((OPTIND-1))

if [ $# -eq 0 ]; then
    if [ -f test.hal -o -f test.sh ]; then
        set -- .
    else
        set -- $TOPDIR/tests
    fi
fi

if [ $CLEAN_ONLY -eq 1 ]; then
    clean "$@"
else
    run_tests "$@"
fi
