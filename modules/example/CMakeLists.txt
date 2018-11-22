#this file CMakeList.txt is used to build a project which is in a module,
#it should be put in a folder "cmake" included in a project
cmake_minimum_required(VERSION 3.5)
# ---------------------------------------------------
#   1.define library/execution target name, it MUST be
#     modified as required
# ---------------------------------------------------
set(OBJ_NAME "example")
#TODO##add some definitions only to this project
#TODO#ADD_DEFINITIONS(-DXXX)
#TODO##remove some definitions only to this project
#TODO#remove_definitions(-DXXX)

# ---------------------------------------------------
#   2.get project directory and show project information
# ---------------------------------------------------
####get Project Director, it must be called in the CMakeList.txt which is in the
####folder "cmake" for a Project
#input: _path               input the path of current CMakeLists.txt,
#                           usually take ${CMAKE_CURRENT_SOURCE_DIR} as an input;
#output:VXL_PROJECT_DIR     define the absolute path of the project,
#                           it is visible in the project cmakelists.txt;
#getVxlProjectDir(${CMAKE_CURRENT_SOURCE_DIR})
set(VXL_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
####print common used variables in project
#input: _projectName   usually input the name of the target
showProjectInfo(${OBJ_NAME})

# ---------------------------------------------------
#   3.find 3rd party library, and add the include directory
#     and library directory to current project,
#     it MUST be modified\added\removed as required.
#     set "XXXX_LIB_LIST_EX" is optional, this is used to specify
#     the library by users. when it is commented, system will using
#     default libraries defined in module script.
# ---------------------------------------------------
#TODO#set(OPENCV_LIB_LIST_EX core imgproc highgui)
#TODO#include(${VXL_TRUNK_DIR}/src/cmake/VxlCfgLibOpenCV.cmake)
#TODO#include_directories(${OPENCV_INCLUDES})
#TODO#link_directories(${OPENCV_LIB_DIR})

#TODO#include(${VXL_TRUNK_DIR}/src/cmake/VxlCfgLibOpenCL.cmake)
#TODO#include_directories(${OPENCL_INCLUDES})
#TODO#link_directories(${OPENCL_LIB_DIR})

#TODO#set(XXXX_LIB_LIST_EX aaa bbb)
#TODO#include(${VXL_TRUNK_DIR}/src/cmake/XXXX.cmake)
#TODO#include_directories(${XXXX_INCLUDES})
#TODO#link_directories(${XXXX_LIB_DIR})

# ---------------------------------------------------
#   4.add include directories to current project, it MUST be
#     modified\added\removed as required
# ---------------------------------------------------
include_directories(${VXL_TRUNK_DIR}/common/interface)
#TODO#include_directories(${VXL_TRUNK_DIR}/src/common/utils/src)
#TODO#include_directories(${VXL_TRUNK_DIR}/src/common/exception/src)
#TODO#include_directories(${VXL_TRUNK_DIR}/src/common/logger/src)
#TODO#include_directories(${VXL_TRUNK_DIR}/src/wrapper/openCV/src)
#TODO#include_directories(${VXL_TRUNK_DIR}/src/wrapper/openCL/src)
include_directories(${VXL_PROJECT_DIR}/include)

# ---------------------------------------------------
#   5.add source files to current project
# ---------------------------------------------------
file(GLOB_RECURSE SRC_LIST
    "${VXL_PROJECT_DIR}/src/*.*"
    "${VXL_PROJECT_DIR}/include/*.*")

# ---------------------------------------------------
#   6.add extra source files to current project, it MUST be
#     modified\added\removed as required
# ---------------------------------------------------
#TODO#list(APPEND SRC_LIST ${VXL_TRUNK_DIR}/src/common/exception/src/vxlException.h)
#TODO#list(APPEND SRC_LIST ${VXL_TRUNK_DIR}/src/common/exception/src/vxlException.cpp)
#TODO#list(APPEND SRC_LIST ${VXL_TRUNK_DIR}/src/common/logger/src/vxlLog.h)
#TODO#list(APPEND SRC_LIST ${VXL_TRUNK_DIR}/src/common/logger/src/vxlLog.cpp)
#TODO#list(APPEND SRC_LIST ${VXL_TRUNK_DIR}/src/wrapper/openCV/src/cvMarket.h)
#TODO#list(APPEND SRC_LIST ${VXL_TRUNK_DIR}/src/wrapper/openCV/src/cvMarket.cpp)

# ---------------------------------------------------
#   7.define version source file, it MUST be commented\uncommented
#     as required, if the generated object should be publish with the
#     version label, under code MUST be uncommented.
# ---------------------------------------------------
#TODO#set(VERSION_RC)
#TODO#if (WIN32)
#TODO#    set(VERSION_RC ${VXL_PROJECT_DIR}/rc/${OBJ_NAME}.rc)
#TODO#endif()

# ---------------------------------------------------
#   8.build STATIC\SHARED library or executable object, it
#     MUST be commented\uncommented as required.
#     NOTE that three types of object are used popularly,
#     therefore under code have provided there prototypes
#     for common usage. users MUST choose one of the under
#     method and comment other methods. on the other way,
#     users CAN create your customized object and comment
#     all of the under methods.
# ---------------------------------------------------
#TODO##add the pre-define macro before creating shared(dynamic) library
addProjDllExport(${OBJ_NAME})
add_library(${OBJ_NAME} SHARED ${SRC_LIST} ${VERSION_RC})

#TODO##create static library
#TODO#add_library(${OBJ_NAME} STATIC ${SRC_LIST} ${VERSION_RC})

#TODO##create executable object
#TODO#add_executable(${OBJ_NAME} ${SRC_LIST})

# ---------------------------------------------------
#   9.link 3rd party library to target, it MUST be 
#     modified\added\removed as required. two methods
#     are provided here, choose one proper method according
#     the library (list) generated in STEP-3.
# ---------------------------------------------------
#TODO##generated libraries "OPENCV_LIBS_DBG" are only used with debug configuration
#TODO#foreach(_lib ${OPENCV_LIBS_DBG})
#TODO#    target_link_libraries(${OBJ_NAME} debug ${_lib})
#TODO#endforeach()

#TODO##generated libraries "OPENCV_LIBS_REL" are not used with no-debug configuration
#TODO#foreach(_lib ${OPENCV_LIBS_REL})
#TODO#    target_link_libraries(${OBJ_NAME} optimized ${_lib})
#TODO#endforeach()

#TODO#foreach(_lib ${XXXX_LIBS_DBG})
#TODO#    target_link_libraries(${OBJ_NAME} debug ${_lib})
#TODO#endforeach()
#TODO#foreach(_lib ${XXXX_LIBS_REL})
#TODO#    target_link_libraries(${OBJ_NAME} optimized ${_lib})
#TODO#endforeach()

#TODO##generated libraries "OPENCL_LIBS" are used in all configurations
#TODO#target_link_libraries(${OBJ_NAME} ${OPENCL_LIBS})

#TODO##generated libraries "YYYY_LIBS" and "ZZZZ_LIBS" are used in all configurations
#TODO#target_link_libraries(${OBJ_NAME} ${YYYY_LIBS})
#TODO#target_link_libraries(${OBJ_NAME} ${ZZZZ_LIBS})

# ---------------------------------------------------
#   10.set project dependencies,link compiled library,
#     it MUST be modified\added\removed as required
# ---------------------------------------------------
#TODO##build the dependence relationship
#TODO#add_dependencies(${OBJ_NAME} "moduleTempLate")
#TODO##link the customized library to target
#TODO#target_link_libraries(${OBJ_NAME} "moduleTempLate")

#TODO##build the dependence relationship
#TODO#add_dependencies(${OBJ_NAME} "moduleXXXX")
#TODO##link the customized library to target
#TODO#target_link_libraries(${OBJ_NAME} "moduleXXXX")

#TODO##build the dependence relationship
#TODO#add_dependencies(${OBJ_NAME} "moduleYYYY")
#TODO##link the customized library to target
#TODO#target_link_libraries(${OBJ_NAME} "moduleYYYY")

# ---------------------------------------------------
#   11.set the target output direction, it MUST be
#     modified as required
# ---------------------------------------------------
#set up target output directory for a project
#input: _objName    name of the output object 
#       _libDir     the absolute directory to for generated library file,
#                   it should be set correctly when generate STATIC_LIBRARY
#                   or SHARED_LIBRARY, otherwise set to NULL
#       _binDir     the absolute directory to for generated *.dll file,
#                   it should be set correctly when generate SHARED_LIBRARY,
#                   otherwise set to NULL
#       _exeDir     the absolute directory to for generated executable file,
#                   it should be set correctly when generate executable,
#                   otherwise set to NULL
#TODO##if the output files belong to product package and the suffixes are dll\lib\so\a
#TODO#setTargetOutputDir(${OBJ_NAME}
#TODO#    ${VXL_PROJECT_DIR}/build/lib
#TODO#    ${VXL_PROJECT_DIR}/build/bin
#TODO#    NULL)

#TODO##if the output files belong to product package and the suffixes are exe\out
#TODO#setTargetOutputDir(${OBJ_NAME}
#TODO#    NULL
#TODO#    NULL
#TODO#    ${VXL_PROJECT_DIR}/build/bin)

#TODO##if the output files only belong to test package
#TODO#setTargetOutputDir(${OBJ_NAME}
#TODO#    NULL
#TODO#    NULL
#TODO#    ${VXL_PROJECT_DIR}/../install)

# ---------------------------------------------------
#   12.set preBuild and postBuild event, it MUST be
#      commented\uncommented as required
# ---------------------------------------------------
#TODO#if(WIN32)
#TODO#    execute_process(
#TODO#        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/preBuild.bat
#TODO#    )
#TODO#    add_custom_command(TARGET ${OBJ_NAME}
#TODO#        POST_BUILD
#TODO#        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/postBuild.bat
#TODO#        COMMENT "This command will be executed after building target"
#TODO#    )
#TODO#elseif(UNIX)
#TODO#    execute_process(
#TODO#        COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/preBuild.sh
#TODO#    )
#TODO#    add_custom_command(TARGET ${OBJ_NAME}
#TODO#        POST_BUILD
#TODO#        COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/postBuild.sh
#TODO#        COMMENT "This command will be executed after building target"
#TODO#    )
#TODO#else()
#TODO#endif()