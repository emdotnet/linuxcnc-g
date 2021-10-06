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
