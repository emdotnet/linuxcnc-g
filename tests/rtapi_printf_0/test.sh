#!/bin/bash -xe

g++ -DULAPI -I${EMC2_INCLUDE_DIR} -std=c++0x \
    -DSIM -rdynamic -L${LIBDIR} \
    -o test_rtapi_vsnprintf test_rtapi_vsnprintf.c
./test_rtapi_vsnprintf
