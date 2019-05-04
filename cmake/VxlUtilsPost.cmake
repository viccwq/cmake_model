set (CMAKE_CXX_STANDARD 11)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

#add global predefine macro
ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)
ADD_DEFINITIONS(-D_CONSOLE)
#ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB)

#SET(BOOST_ROOT_DIR "$ENV{BOOST_DIR}")


#if(WIN32)
#SET(BOOST_INC_DIR "${BOOST_ROOT_DIR}include/boost-1_66/")
#SET(BOOST_LIB_DIR "${BOOST_ROOT_DIR}lib\\")
#elseif(UNIX)
#SET(BOOST_INC_DIR "${BOOST_ROOT_DIR}/include/")
#SET(BOOST_LIB_DIR "${BOOST_ROOT_DIR}/lib/")
#endif(WIN32)


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5")
    message(FATAL_ERROR "Insufficient gcc version" ${CMAKE_CXX_COMPILER_VERSION})
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  if(MSVC_VERSION VERSION_EQUAL "1800")
    message("msvc version:" ${MSVC_VERSION})
    set(MSVC_BUILD_VER vc120)
  elseif(MSVC_VERSION VERSION_EQUAL "1900")
    message("msvc version:" ${MSVC_VERSION})
    set(MSVC_BUILD_VER vc140)
  else()
    message("unknown msvc version:" ${MSVC_VERSION})
  endif(MSVC_VERSION VERSION_EQUAL "1800")
endif()

#if(LINUX)
#    set(ADDLINKEDLIBS "boost_system" "boost_thread" "boost_filesystem" "rt" "pthread" "dl")
#elseif(APPLE)
#    set(ADDLINKEDLIBS "boost_system" "boost_thread" "boost_filesystem" "pthread" "dl")
#elseif(WIN32)
#	if(NOT "${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
#		set(ADDLINKEDLIBS "libboost_chrono-${MSVC_BUILD_VER}-mt-sgd-x32-1_66.lib" "libboost_date_time-${MSVC_BUILD_VER}-mt-sgd-x32-1_66.lib" "libboost_system-${MSVC_BUILD_VER}-mt-sgd-x32-1_66.lib" "libboost_thread-${MSVC_BUILD_VER}-mt-sgd-x32-1_66.lib" "libboost_filesystem-${MSVC_BUILD_VER}-mt-sgd-x32-1_66.lib")
#	else()
#		set(ADDLINKEDLIBS "libboost_chrono-${MSVC_BUILD_VER}-mt-sgd-x64-1_66.lib" "libboost_date_time-${MSVC_BUILD_VER}-mt-sgd-x64-1_66.lib" "libboost_system-${MSVC_BUILD_VER}-mt-sgd-x64-1_66.lib" "libboost_thread-${MSVC_BUILD_VER}-mt-sgd-x64-1_66.lib" "libboost_filesystem-${MSVC_BUILD_VER}-mt-sgd-x64-1_66.lib")
#	endif()
#endif(LINUX)

set(CompilerFlags
    CMAKE_CXX_FLAGS
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_RELWITHDEBINFO
    CMAKE_CXX_FLAGS_MINSIZEREL
    CMAKE_C_FLAGS
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_RELWITHDEBINFO
    CMAKE_C_FLAGS_MINSIZEREL)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    foreach(CompilerFlag ${CompilerFlags})
        string(CONCAT ${CompilerFlag} "${${CompilerFlag}}" " -m64")
    endforeach()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    foreach(CompilerFlag ${CompilerFlags})
#        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif()

if (WIN32)
ADD_DEFINITIONS(-D_WIN32)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
elseif(UNIX)
ADD_DEFINITIONS(-D__linux__)
ADD_DEFINITIONS(-fpermissive)
####note: the performances of global variables in shared lib in linux are totally different from those in windows, which can be refered in https://blog.csdn.net/imxiangzi/article/details/45872025
####      here we use -fpie -fvisibility=hidden to avoid the performance
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpie -fvisibility=hidden")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fpie -fvisibility=hidden")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fpie -fvisibility=hidden")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -fpie -fvisibility=hidden")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -fpie -fvisibility=hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpie -fvisibility=hidden")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fpie -fvisibility=hidden")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fpie -fvisibility=hidden")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -fpie -fvisibility=hidden")
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -fpie -fvisibility=hidden")
else()

endif()

#generate config file
configure_file(${VXL_TRUNK_DIR}/common/interface/vxlCmakeCfg.h.in ${VXL_TRUNK_DIR}/common/interface/vxlCmakeCfg.h)

####get Project Director, it must be called in the CMakeList.txt which is in the
####folder "cmake" for a Project
#input: _path               input the path of current CMakeLists.txt, 
#                           usually take ${CMAKE_CURRENT_SOURCE_DIR} as an input;
#output:VXL_PROJECT_DIR     define the absolute path of the project, 
#                           it is visible in the project cmakelists.txt;
macro(getVxlProjectDir _path)
    string(FIND ${_path} "/cmake" index REVERSE)
    string(SUBSTRING ${_path} "0" ${index} VXL_PROJECT_DIR)
    unset(index)
endmacro()

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
macro(setTargetOutputDir _objName _libDir _binDir _exeDir)
    #get_target_property, if it is an executable or a library
    get_property(targetProp TARGET ${_objName} PROPERTY TYPE)
    message(STATUS "Target type is:" ${targetProp})
    if(WIN32)
        if(CMAKE_SIZEOF_VOID_P)
            set(platFormDir "/x64")
        else()
            set(platFormDir "/x86")
        endif()

        if(${targetProp} STREQUAL "EXECUTABLE")
            set(OBJ_RUNTIME_OUTPUT_DIR ${_exeDir}${platFormDir})
        elseif(${targetProp} STREQUAL "STATIC_LIBRARY")
            set(OBJ_ARCHIVE_OUTPUT_DIR ${_libDir}${platFormDir})
        elseif(${targetProp} STREQUAL "SHARED_LIBRARY")
            set(OBJ_RUNTIME_OUTPUT_DIR ${_binDir}${platFormDir})
            set(OBJ_ARCHIVE_OUTPUT_DIR ${_libDir}${platFormDir})
            set(OBJ_LIBRARY_OUTPUT_DIR ${_libDir}${platFormDir})
        else()
        endif()
        unset(platFormDir CACHE)
    elseif(UNIX)
        set(platFormDir "/x64")
        if(${targetProp} STREQUAL "EXECUTABLE")
            set(OBJ_RUNTIME_OUTPUT_DIR ${_exeDir}${platFormDir})
        elseif(${targetProp} STREQUAL "STATIC_LIBRARY")
            set(OBJ_ARCHIVE_OUTPUT_DIR ${_libDir}${platFormDir})
        elseif(${targetProp} STREQUAL "SHARED_LIBRARY")
            set(OBJ_RUNTIME_OUTPUT_DIR ${_binDir}${platFormDir})
            set(OBJ_ARCHIVE_OUTPUT_DIR ${_libDir}${platFormDir})
            set(OBJ_LIBRARY_OUTPUT_DIR ${_libDir}${platFormDir})
        else()
        endif()
        unset(platFormDir CACHE)
    endif()
    unset(targetProp CACHE)
    
    #set project properties
    set_target_properties(${_objName} PROPERTIES
        ARCHIVE_OUTPUT_NAME_DEBUG          ${_objName}d
        LIBRARY_OUTPUT_NAME_DEBUG          ${_objName}d
        RUNTIME_OUTPUT_NAME_DEBUG          ${_objName}d
        ARCHIVE_OUTPUT_NAME_RELEASE        ${_objName}
        LIBRARY_OUTPUT_NAME_RELEASE        ${_objName}
        RUNTIME_OUTPUT_NAME_RELEASE        ${_objName}
        ARCHIVE_OUTPUT_NAME_RELWITHDEBINFO ${_objName}
        LIBRARY_OUTPUT_NAME_RELWITHDEBINFO ${_objName}
        RUNTIME_OUTPUT_NAME_RELWITHDEBINFO ${_objName}
        ARCHIVE_OUTPUT_NAME_MINSIZEREL     ${_objName}m
        LIBRARY_OUTPUT_NAME_MINSIZEREL     ${_objName}m
        RUNTIME_OUTPUT_NAME_MINSIZEREL     ${_objName}m
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          ${OBJ_ARCHIVE_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_DEBUG          ${OBJ_LIBRARY_OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG          ${OBJ_RUNTIME_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        ${OBJ_ARCHIVE_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_RELEASE        ${OBJ_LIBRARY_OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        ${OBJ_RUNTIME_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${OBJ_ARCHIVE_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${OBJ_LIBRARY_OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${OBJ_RUNTIME_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     ${OBJ_ARCHIVE_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL     ${OBJ_LIBRARY_OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     ${OBJ_RUNTIME_OUTPUT_DIR}
        )
endmacro()

####print common used variables in the solution
#input: _projectName   usually input the name of the project
macro(showSolutionInfo _solutionName)
    message(STATUS ">>>>>> creating solution: ${_solutionName} <<<<<<")
    message(STATUS "============= showSolutionInfo =============")
    message(STATUS "PROJECT_NAME             = " ${PROJECT_NAME})    
    message(STATUS "VXL_TRUNK_DIR            = " ${VXL_TRUNK_DIR})
    message(STATUS "PROJECT_SOURCE_DIR       = " ${PROJECT_SOURCE_DIR})
    message(STATUS "PROJECT_BINARY_DIR       = " ${PROJECT_BINARY_DIR})
    message(STATUS "CMAKE_CURRENT_SOURCE_DIR = " ${CMAKE_CURRENT_SOURCE_DIR})
    message(STATUS "CMAKE_CURRENT_BINARY_DIR = " ${CMAKE_CURRENT_BINARY_DIR})
    message(STATUS "CMAKE_GENERATOR_PLATFORM = " ${CMAKE_GENERATOR_PLATFORM})     
    message(STATUS "CMAKE_C_FLAGS_DEBUG            = " ${CMAKE_C_FLAGS_DEBUG})
    message(STATUS "CMAKE_CXX_FLAGS_DEBUG          = " ${CMAKE_CXX_FLAGS_DEBUG})
    message(STATUS "CMAKE_C_FLAGS_RELEASE          = " ${CMAKE_C_FLAGS_RELEASE})
    message(STATUS "CMAKE_CXX_FLAGS_RELEASE        = " ${CMAKE_CXX_FLAGS_RELEASE})
    message(STATUS "CMAKE_C_FLAGS_RELWITHDEBINFO   = " ${CMAKE_C_FLAGS_RELWITHDEBINFO})
    message(STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO = " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
    message(STATUS "============================================")
endmacro()

####print common used variables in project
#input: _projectName   usually input the name of the target
macro(showProjectInfo _projectName)
    message(STATUS ">>>>>> creating project: ${_projectName} <<<<<<")
    message(STATUS "============= showProjectInfo =============")
    message(STATUS "PROJECT_NAME             = " ${PROJECT_NAME})     
    message(STATUS "VXL_TRUNK_DIR            = " ${VXL_TRUNK_DIR})
    message(STATUS "VXL_PROJECT_DIR          = " ${VXL_PROJECT_DIR})
    message(STATUS "CMAKE_CURRENT_SOURCE_DIR = " ${CMAKE_CURRENT_SOURCE_DIR})
    message(STATUS "CMAKE_CURRENT_BINARY_DIR = " ${CMAKE_CURRENT_BINARY_DIR})
    message(STATUS "===========================================")
endmacro()

####add pre-definition to export the interface when compiling shared library
####in windows
#input: _projectName   usually input the name of the target
macro(addProjDllExport _projectName)
    string(TOUPPER ${_projectName} var)
    set(var "-D${var}_EXPORTS")
    add_definitions(${var})
    unset(var CACHE)
endmacro()

####add resource files that can generate the version for dll in windows
#input: _obj_name  
#input: _src_dir   the path including the resource.h and the xxxx.rc
#input: _dst_dir   the path where the resource.h and the xxxx.rc file will be saved
macro(addRcFiles _obj_name _src_dir _dst_dir)
    message(STATUS ${_obj_name})
    message(STATUS ${_src_dir})
    message(STATUS ${_dst_dir})

    configure_file(${_src_dir}/vxlGitVersion.h ${_dst_dir}/vxlGitVersion.h COPYONLY)
    configure_file(${_src_dir}/resource.h.in ${_dst_dir}/resource.h COPYONLY)
    configure_file(${_src_dir}/example.rc.in ${_dst_dir}/${_obj_name}.rc)
endmacro()

####get the file list in specified path, including *.cpp|*.hpp|*.c|*.h|*.cl|*.clh
#input:  _path        specified path to find all source files
#output: SRC_LIST_EX  list all the files in the specified path
macro(getFileList _path)
    set(SRC_LIST_EX "")
    file(GLOB SRC_LIST_EX
    "${_path}/*.cpp"
    "${_path}/*.hpp"
    "${_path}/*.c"
    "${_path}/*.h"
    "${_path}/*.cl"
    "${_path}/*.clh")
    message(STATUS "SRC_LIST_EX:")
    foreach(_item ${SRC_LIST_EX})
        message(STATUS "    ${_item}")
    endforeach()
endmacro()
