#previously this was linuxcncini.so
add_library(inifile SHARED inifile.cc)
set_property(TARGET inifile PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(inivar inivar.cc)
target_link_libraries(inivar PRIVATE inifile)