#!/bin/sh
gcc -O -I${EMC2_INCLUDE_DIR} test.c -o test -DULAPI -std=gnu99 -pthread || exit 1
./test; exitval=$?
rm -f test
exit $exitval
