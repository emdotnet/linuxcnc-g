cmake_minimum_required(VERSION 3.14)
project(extralib)

SET(EMC2_CMAKE_DIR "$ENV{EMC2_CMAKE_DIR}")

if (EMC2_CMAKE_DIR)
else()
	message( FATAL_ERROR  "EMC2_CMAKE_DIR is undefined")
endif()

SET(EMC2_INCLUDE_DIR "$ENV{EMC2_INCLUDE_DIR}")

if (EMC2_INCLUDE_DIR)
else()
	message( FATAL_ERROR  "EMC2_INCLUDE_DIR is undefined")
endif()

list(APPEND CMAKE_MODULE_PATH ${EMC2_CMAKE_DIR})

include(buildoptions)
include(buildcomponent)

include_directories(${EMC2_INCLUDE_DIR})

compile_component(extralib extralib_test.comp ON)
