
export PIDOF="pidof -x"
export PS=ps
export AWK=awk
export GREP=grep
export IPCS=ipcs
export KILL=kill

export THIS=$(basename $0)

export RUN_IN_PLACE=yes
export RTPREFIX="uspace"

export DEBUG_FILE=$(mktemp /tmp/linuxcnc.debug.XXXXXX)
export PRINT_FILE=$(mktemp /tmp/linuxcnc.print.XXXXXX)

export RTS=0

rpath=$(dirname `realpath $0`)

export EMC2_HOME=${rpath}/..
export EMC2_HOME_DIR=${rpath}/..
export EMC2_BIN_DIR=${rpath}/../bin
export EMC2_LIB_DIR=${rpath}/../lib/
export EMC2_RTLIB_DIR=${rpath}/../rtlib/
export EMC2_CMAKE_DIR=${rpath}/../cmake/
export EMC2_INCLUDE_DIR=${rpath}/../include/
export EMC2_TCL_DIR=${EMC2_HOME_DIR}/tcl
export EMC2_TCL_BIN_DIR=${EMC2_HOME_DIR}/tcl
export EMC2_TCL_SCRIPTS_DIR=${EMC2_HOME_DIR}/tcl
export EMC2_TCL_LIB_DIR=${EMC2_HOME_DIR}/tcl
export EMC2_HELP_DIR=${EMC2_HOME_DIR}/docs/help
export EMC2_NCFILES_DIR=${EMC2_HOME_DIR}/../nc_files
export EMC2_LANG_DIR=${EMC2_HOME_DIR}/objects
export EMC2_IMAGE_DIR=${rpath}/../images/
export HAL_RTMOD_DIR=${rpath}/../rtlib/
export HALLIB_DIR=${rpath}/../hallib/
export LINUXCNC_AUX_GLADEVCP=${rpath}/../aux/
export LINUXCNC_AUX_EXAMPLES=${rpath}/../aux/examples
export LINUXCNC_CONFIG_PATH=${EMC2_HOME_DIR}/../configs/

export EMC2_DEFAULT_NMLFILE=${LINUXCNC_CONFIG_PATH}/common/linuxcnc_big.nml
export EMC2_DEFAULT_TOOLTABLE=${LINUXCNC_CONFIG_PATH}/sim/sim.tbl

export PATH=${PATH}:${EMC2_BIN_DIR}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${EMC2_LIB_DIR}
export PYTHONPATH=${EMC2_HOME_DIR}/python:${EMC2_HOME_DIR}/lib

export LIBDIR=${EMC2_LIB_DIR}

export MODULE_EXT=.so

export LINUXCNC_HOME=${EMC2_HOME_DIR}
export LINUXCNC_BIN_DIR=${EMC2_BIN_DIR}
export LINUXCNC_LIB_DIR=${EMC2_LIB_DIR}
export LINUXCNC_RTLIB_DIR=${EMC2_RTLIB_DIR}
export LINUXCNCVERSION="3.0.0"

export REALTIME=${EMC2_BIN_DIR}/realtime
export LINUXCNC_TCL_DIR=${EMC2_HOME_DIR}/tcl

# export LINUXCNC_HELP_DIR=/home/end/projects/linuxcnc/docs/help
# export LINUXCNC_RTLIB_DIR=/home/end/projects/linuxcnc/rtlib
# export LINUXCNC_CONFIG_PATH="~/linuxcnc/configs:/home/end/projects/linuxcnc/configs"
# export LINUXCNC_NCFILES_DIR=/home/end/projects/linuxcnc/nc_files
# export LINUXCNC_LANG_DIR=/home/end/projects/linuxcnc/src/objects
# export REALTIME=/home/end/projects/linuxcnc/scripts/realtime
# export LINUXCNC_IMAGEDIR=/home/end/projects/linuxcnc
# export LINUXCNC_TCL_LIB_DIR=/home/end/projects/linuxcnc/tcl
# export HALLIB_DIR=/home/end/projects/linuxcnc/lib/hallib; export HALLIB_DIR
# export HALLIB_PATH=.:$HALLIB_DIR; export HALLIB_PATH
