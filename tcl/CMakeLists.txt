add_custom_command(
        OUTPUT linuxcnc.tcl
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/linuxcnc.tcl
        ${PROJECT_BINARY_DIR}/tcl/linuxcnc.tcl
)
add_custom_command(
        OUTPUT pickconfig.tcl
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/bin/pickconfig.tcl
        ${PROJECT_BINARY_DIR}/tcl/pickconfig.tcl
)

add_custom_target(tclfiles ALL DEPENDS linuxcnc.tcl pickconfig.tcl)
