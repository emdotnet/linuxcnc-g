
# specify default C compiler options

SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
# debug flags
if(NOT DEBUG)
  set(CMAKE_C_FLAGS -Wall\ -O2)
else()
  set(CMAKE_C_FLAGS -Wall\ -rdynamic\ -fvisibility=default\ -Wall\ -O0\ -g\ -fsanitize=address\ -fno-omit-frame-pointer)
endif()

# specify the default C++ compiler options
# change standard to 20 as soon as possible
# (need gcc8, gcc7 allows 17)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(NOT DEBUG)
    set(CMAKE_CXX_FLAGS -Wall\ -O2)
else()
    set(CMAKE_CXX_FLAGS -Wall\ -rdynamic\ -fvisibility=default\ -O0\ -g\ -fsanitize=address\ -fno-omit-frame-pointer)
endif()

set(RTLIB_DIR ${PROJECT_BINARY_DIR}/rtlib)