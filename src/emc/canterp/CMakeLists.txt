add_library(canterp SHARED canterp.cc)
target_link_libraries(canterp nmlintf rs274ngc)

set_property(TARGET canterp PROPERTY POSITION_INDEPENDENT_CODE ON)
