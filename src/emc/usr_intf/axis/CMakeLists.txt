add_library(emcmodule SHARED extensions/emcmodule.cc)
target_link_libraries(emcmodule PRIVATE Python3::Python)
target_link_libraries(emcmodule PRIVATE nmlintf)
target_link_libraries(emcmodule PRIVATE nml)
target_link_libraries(emcmodule PRIVATE ulapi)
target_link_libraries(emcmodule PRIVATE inifile)
target_link_libraries(emcmodule PRIVATE tooldata)
target_link_libraries(emcmodule PRIVATE ${EPOXY_LIBRARIES})
get_uspace_config(emcmodule)

set_target_properties(emcmodule PROPERTIES POSITION_INDEPENDENT_CODE ON
                                           PREFIX ""
                                           LIBRARY_OUTPUT_NAME emcmodule)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(_togl SHARED extensions/_toglmodule.c)
target_link_libraries(_togl PRIVATE Python3::Python)
target_link_libraries(_togl PRIVATE ${TCL_LIBRARY})
target_link_libraries(_togl PRIVATE ${TK_LIBRARY})
target_link_libraries(_togl PRIVATE X11::Xmu)

set_target_properties(_togl PROPERTIES PREFIX "")