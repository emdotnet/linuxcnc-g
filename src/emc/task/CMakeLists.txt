add_executable(linuxcncsvr emcsvr.cc)
target_link_libraries(linuxcncsvr PRIVATE hal nml nmlintf inifile)
get_uspace_config(linuxcncsvr)

set(MILL_SOURCES
        ../motion/emcmotglb.c
        ../task/emctask.cc
        ../task/emccanon.cc
        ../task/emctaskmain.cc
        ../motion/usrmotintf.cc
        ../motion/emcmotutil.c
        ../task/taskintf.cc
        ../motion/dbuf.c
        ../motion/stashf.c
        ../task/taskmodule.cc
        ../task/taskclass.cc
        ../task/backtrace.cc)
add_executable(milltask ${MILL_SOURCES})
target_link_libraries(milltask PRIVATE Boost::${BOOSTPYTHON})
target_link_libraries(milltask PRIVATE hal)
target_link_libraries(milltask PRIVATE nml)
target_link_libraries(milltask PRIVATE nmlintf)
target_link_libraries(milltask PRIVATE inifile)
target_link_libraries(milltask PRIVATE Python3::Python)
target_link_libraries(milltask PRIVATE pythonplugin)
target_link_libraries(milltask PRIVATE posemath)
target_link_libraries(milltask PRIVATE rs274ngc)
target_link_libraries(milltask PRIVATE tooldata)
get_uspace_config(milltask)
