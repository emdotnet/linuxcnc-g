set(NMLINTF_SOURCES
        ../nml_intf/emcglb.c
        ../rs274ngc/modal_state.cc
        ../nml_intf/emc.cc
        ../nml_intf/emcpose.c
        ../nml_intf/emcargs.cc
        ../nml_intf/emcops.cc
        ../nml_intf/canon_position.cc
        ../ini/emcIniFile.cc
        ../ini/iniaxis.cc
        ../ini/inijoint.cc
        ../ini/initraj.cc
        ../ini/inihal.cc
        ../nml_intf/interpl.cc
        )

add_library(nmlintf STATIC ${NMLINTF_SOURCES})
set_property(TARGET nmlintf PROPERTY POSITION_INDEPENDENT_CODE ON)
get_uspace_config(nmlintf)
#target_link_libraries(linuxcnc PRIVATE Python3::Module)
#target_link_libraries(linuxcnc PRIVATE pythonplugin)
#get_uspace_config(linuxcnc)