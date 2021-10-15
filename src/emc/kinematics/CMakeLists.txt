set(GENSERKINS_SOURCES
        ugenserkins.c
        genserfuncs.c)

add_executable(genserkins ${GENSERKINS_SOURCES})
target_link_libraries(genserkins PRIVATE hal)
target_link_libraries(genserkins PRIVATE posemath)
target_link_libraries(genserkins PRIVATE m)
get_uspace_config(genserkins)

add_library(l_lineardeltakins SHARED lineardeltakins.cc)
target_link_libraries(l_lineardeltakins PRIVATE ${BOOST_LIBS})
target_link_libraries(l_lineardeltakins PRIVATE Python3::Python)
target_link_libraries(l_lineardeltakins PRIVATE hal)
target_link_libraries(l_lineardeltakins PRIVATE posemath)
get_uspace_config(l_lineardeltakins)

add_library(l_rotarydeltakins SHARED rotarydeltakins.cc)
target_link_libraries(l_rotarydeltakins PRIVATE ${BOOST_LIBS})
target_link_libraries(l_rotarydeltakins PRIVATE Python3::Python)
target_link_libraries(l_rotarydeltakins PRIVATE hal)
target_link_libraries(l_rotarydeltakins PRIVATE posemath)
get_uspace_config(l_rotarydeltakins)
