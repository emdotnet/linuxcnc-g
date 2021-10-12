set(TOOLDATA_SOURCES
        tooldata_common.cc
        tooldata_db.cc
        tool_watch.cc
        )

add_library(tooldata ${TOOLDATA_SOURCES})
get_uspace_config(tooldata)
set_property(TARGET tooldata PROPERTY POSITION_INDEPENDENT_CODE ON)

if(${TOOL_NML})
    target_sources(tooldata PRIVATE
            tooldata_nml.cc
            )
else()
    message(FATAL_ERROR "unimplemented, please use nml.")
endif()

add_executable(tooldata_watch tool_watch.cc)
target_link_libraries(tooldata_watch PRIVATE Python3::Python)
target_link_libraries(tooldata_watch PRIVATE inifile)
target_link_libraries(tooldata_watch PRIVATE tooldata)
target_link_libraries(tooldata_watch PRIVATE nml)
target_link_libraries(tooldata_watch PRIVATE nmlintf)
get_uspace_config(tooldata_watch)
