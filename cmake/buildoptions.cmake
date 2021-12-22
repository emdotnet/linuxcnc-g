
# specify default C compiler options

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
# debug flags
if(NOT DEBUG)
  set(CMAKE_C_FLAGS -Wall\ -O2)
else()
  set(CMAKE_C_FLAGS -rdynamic\ -fvisibility=default\ -Wall\ -O0\ -g)
endif()

# specify the default C++ compiler options
# change standard to 20 as soon as possible
# (need gcc8, gcc7 allows 17)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(NOT DEBUG)
    set(CMAKE_CXX_FLAGS -Wall\ -O2)
else()
    set(CMAKE_CXX_FLAGS -rdynamic\ -fvisibility=default\ -Wall\ -O0\ -g)
endif()
