add_executable(motion-logger motion-logger.c)
target_link_libraries(motion-logger nmlintf hal)
target_compile_definitions(motion-logger PRIVATE ULAPI)
