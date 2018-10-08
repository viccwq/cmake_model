#this file CMakeList.txt is used to build a project which is in a module,
#it should be put in a folder "cmake" included in a project
cmake_minimum_required(VERSION 3.5)
# ---------------------------------------------------
#   1.define library/execution target name, it MUST be
#     modified as required
# ---------------------------------------------------
set(OBJ_NAME "tmvDetectPyrStatic")
ADD_DEFINITIONS(-DNOMINMAX)
# ---------------------------------------------------
#   2.get project directory and show project information
# ---------------------------------------------------
####get Project Director, it must be called in the CMakeList.txt which is in the
####folder "cmake" for a Project
#input: _path               input the path of current CMakeLists.txt,
#                           usually take ${CMAKE_CURRENT_SOURCE_DIR} as an input;
#output:VCA_PROJECT_DIR     define the absolute path of the project,
#                           it is visible in the project cmakelists.txt;
getVcaProjectDir(${CMAKE_CURRENT_SOURCE_DIR})
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
set(OPENCV_LIB_LIST_EX core imgproc highgui)
include(${VCA_TRUNK_DIR}/src/cmake/VcaCfgLibOpenCV.cmake)
include_directories(${OPENCV_INCLUDES})
link_directories(${OPENCV_LIB_DIR})

include(${VCA_TRUNK_DIR}/src/cmake/VcaCfgLibOpenCL.cmake)
include_directories(${OPENCL_INCLUDES})
link_directories(${OPENCL_LIB_DIR})

# ---------------------------------------------------
#   4.add include directories to current project, it MUST be
#     modified\added\removed as required
# ---------------------------------------------------
include_directories(${VCA_TRUNK_DIR}/src/common/interface)
include_directories(${VCA_TRUNK_DIR}/src/common/utils/src)
include_directories(${VCA_TRUNK_DIR}/src/common/exception/src)
include_directories(${VCA_TRUNK_DIR}/src/common/logger/src)
include_directories(${VCA_TRUNK_DIR}/src/wrapper/openCV/src)
include_directories(${VCA_TRUNK_DIR}/src/wrapper/openCL/src)
include_directories(${VCA_TRUNK_DIR}/src/vp2/imageFilter/src)
include_directories(${VCA_TRUNK_DIR}/src/vp2/matFactory/utils/src)
include_directories(${VCA_PROJECT_DIR}/interface)
include_directories(${VCA_PROJECT_DIR}/src)

# ---------------------------------------------------
#   5.add source files to current project
# ---------------------------------------------------
file(GLOB_RECURSE SRC_LIST
    "${VCA_PROJECT_DIR}/src/*.*"
    "${VCA_PROJECT_DIR}/interface/*.*")

# ---------------------------------------------------
#   6.add extra source files to current project, it MUST be
#     modified\added\removed as required
# ---------------------------------------------------
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/common/utils/src/vcaPortableFuncs.h)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/common/utils/src/vcaPortableFuncs.cpp)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/common/exception/src/vcaException.h)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/common/exception/src/vcaException.cpp)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/common/logger/src/vcaLog.h)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/common/logger/src/vcaLog.cpp)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/wrapper/openCV/src/cvMarket.h)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/wrapper/openCV/src/cvMarket.cpp)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/wrapper/openCL/src/oclUtils.hpp)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/wrapper/openCL/src/oclUtils.cpp)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/vp2/imageFilter/src/resize.h)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/vp2/imageFilter/src/resize.cpp)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/vp2/imageFilter/src/resizeOcl.h)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/vp2/imageFilter/src/resizeOcl.cpp)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/vp2/matFactory/utils/src/oclMemFuncs.h)
list(APPEND SRC_LIST ${VCA_TRUNK_DIR}/src/vp2/matFactory/utils/src/oclMemFuncs.cpp)
# ---------------------------------------------------
#   7.define version source file, it MUST be commented\uncommented
#     as required, if the generated object should be publish with the
#     version label, under code MUST be uncommented.
# ---------------------------------------------------
set(VERSION_RC)
if (WIN32)
#    set(VERSION_RC ${VCA_PROJECT_DIR}/rc/${OBJ_NAME}.rc)
endif()

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
#add the pre-define macro before creating shared(dynamic) library
#addProjDllExport(${OBJ_NAME})
#add_library(${OBJ_NAME} SHARED ${SRC_LIST} ${VERSION_RC})

#create static library
add_library(${OBJ_NAME} STATIC ${SRC_LIST} ${VERSION_RC})

#create executable object
#add_executable(${OBJ_NAME} ${SRC_LIST})

# ---------------------------------------------------
#   9.link 3rd party library to target, it MUST be 
#     modified\added\removed as required. two methods
#     are provided here, choose one proper method according
#     the library (list) generated in STEP-3.
# ---------------------------------------------------
#generated libraries "OPENCV_LIBS_DBG" are only used with debug configuration
foreach(_lib ${OPENCV_LIBS_DBG})
    target_link_libraries(${OBJ_NAME} debug ${_lib})
endforeach()
#generated libraries "OPENCV_LIBS_REL" are not used with no-debug configuration
foreach(_lib ${OPENCV_LIBS_REL})
    target_link_libraries(${OBJ_NAME} optimized ${_lib})
endforeach()

#foreach(_lib ${XXXX_LIBS_DBG})
#    target_link_libraries(${OBJ_NAME} debug ${_lib})
#endforeach()
#foreach(_lib ${XXXX_LIBS_REL})
#    target_link_libraries(${OBJ_NAME} optimized ${_lib})
#endforeach()

#generated libraries "OPENCL_LIBS" are used in all configurations
target_link_libraries(${OBJ_NAME} ${OPENCL_LIBS})

#generated libraries "YYYY_LIBS" and "ZZZZ_LIBS" are used in all configurations
#target_link_libraries(${OBJ_NAME} ${YYYY_LIBS})
#target_link_libraries(${OBJ_NAME} ${ZZZZ_LIBS})

# ---------------------------------------------------
#   10.set project dependencies,link compiled library,
#     it MUST be modified\added\removed as required
# ---------------------------------------------------
#build the dependence relationship
#add_dependencies(${OBJ_NAME} "moduleXXXX")
#link the customized library to target
#target_link_libraries(${OBJ_NAME} "moduleXXXX")

#build the dependence relationship
#add_dependencies(${OBJ_NAME} "moduleYYYY")
#link the customized library to target
#target_link_libraries(${OBJ_NAME} "moduleYYYY")

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
setTargetOutputDir(${OBJ_NAME}
    ${VCA_PROJECT_DIR}/build/lib
    ${VCA_PROJECT_DIR}/build/bin
    NULL)

# ---------------------------------------------------
#   12.set preBuild and postBuild event, it MUST be
#      commented\uncommented as required
# ---------------------------------------------------
if(WIN32)
    execute_process(
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/runCl2hl.bat
    )
#TODO#    add_custom_command(TARGET ${OBJ_NAME}
#TODO#        POST_BUILD
#TODO#        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/postBuild.bat
#TODO#        COMMENT "This command will be executed after building target"
#TODO#    )
elseif(UNIX)
    execute_process(
        COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/runCl2hl.sh
    )
#TODO#    add_custom_command(TARGET ${OBJ_NAME}
#TODO#        POST_BUILD
#TODO#        COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/postBuild.sh
#TODO#        COMMENT "This command will be executed after building target"
#TODO#    )
else()
endif()
