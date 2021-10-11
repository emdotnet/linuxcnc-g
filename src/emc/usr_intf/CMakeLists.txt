set(EMCSH_SOURCES
        emcsh.cc
        shcom.cc
        )

set(EMCRSH_SOURCES
        emcrsh.cc
        shcom.cc
        )

set(EMCSCHED_SOURCES
        schedrmt.cc
        emcsched.cc
        shcom.cc
        )

set(EMCLCD_SOURCES
        emclcd.cc
        shcom.cc
        sockets.c
        )
set(HALUI_SOURCES
        halui.cc
        )

add_library(linuxcnc SHARED ${EMCSH_SOURCES})
target_include_directories(linuxcnc PRIVATE ${TCL_INCLUDE_PATH})
target_link_libraries(linuxcnc PRIVATE ${TCL_LIBRARY})
target_link_libraries(linuxcnc PRIVATE X11::Xinerama)
target_link_libraries(linuxcnc PRIVATE Python3::Python)
target_link_libraries(linuxcnc PRIVATE pythonplugin)
target_link_libraries(linuxcnc PRIVATE nml)
target_link_libraries(linuxcnc PRIVATE nmlintf)
target_link_libraries(linuxcnc PRIVATE inifile)
get_uspace_config(linuxcnc)

add_executable(linuxcncrsh ${EMCRSH_SOURCES})
target_link_libraries(linuxcncrsh PRIVATE nml)
target_link_libraries(linuxcncrsh PRIVATE nmlintf)
target_link_libraries(linuxcncrsh PRIVATE inifile)
target_link_libraries(linuxcncrsh PRIVATE halsh)
target_link_libraries(linuxcncrsh PRIVATE ulapi)
get_uspace_config(linuxcncrsh)

add_executable(schedrmt ${EMCSCHED_SOURCES})
target_link_libraries(schedrmt PRIVATE nml)
target_link_libraries(schedrmt PRIVATE nmlintf)
target_link_libraries(schedrmt PRIVATE inifile)
target_link_libraries(schedrmt PRIVATE halsh)
target_link_libraries(schedrmt PRIVATE ulapi)
get_uspace_config(schedrmt)

add_executable(linuxcnclcd ${EMCLCD_SOURCES})
target_link_libraries(linuxcnclcd PRIVATE nml)
target_link_libraries(linuxcnclcd PRIVATE nmlintf)
target_link_libraries(linuxcnclcd PRIVATE inifile)
target_link_libraries(linuxcnclcd PRIVATE halsh)
target_link_libraries(linuxcnclcd PRIVATE ulapi)
get_uspace_config(linuxcnclcd)

add_executable(halui ${HALUI_SOURCES})
target_link_libraries(halui PRIVATE nml)
target_link_libraries(halui PRIVATE nmlintf)
target_link_libraries(halui PRIVATE inifile)
target_link_libraries(halui PRIVATE halsh)
target_link_libraries(halui PRIVATE ulapi)
target_link_libraries(halui PRIVATE hal)
target_link_libraries(halui PRIVATE tooldata)
get_uspace_config(halui)
