if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(WIN32)
    if(NOT "${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
        set(WIN_X86 TRUE)
    else()
        set(WIN_X64 TRUE)
    endif()
endif(WIN32)

if(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug")
    set(BUILD_DEBUG TRUE)
elseif(CMAKE_CONFIGURATION_TYPES STREQUAL "RelWithDebInfo")
    set(BUILD_RELWITHDEBINFO TRUE)
elseif(CMAKE_CONFIGURATION_TYPES STREQUAL "Release")
    set(BUILD_RELEASE TRUE)
elseif(CMAKE_CONFIGURATION_TYPES STREQUAL "Minsizerel")
    set(MINSIZEREL TRUE)
else()
endif()

if(WIN32)
    execute_process(
        COMMAND ${VXL_TRUNK_DIR}/src/cmake/videoSync.bat)
elseif(UNIX)
    execute_process(
        COMMAND sh ${VXL_TRUNK_DIR}/src/cmake/videoSync.sh)
else()
endif()

##get Solution Director, it must be called in the current CMakeList.txt for Solution
#input: _path           input the path of current CMakeLists.txt, 
#                       usually take ${CMAKE_CURRENT_SOURCE_DIR} as an input;
#output:VXL_TRUNK_DIR   define the absolute path of the local trunk,
#                       it is realize by finding the file "trunkToken".
macro(getVxlTrunkDir _path)
    if(NOT(EXISTS ${_path}))
        message(FATAL_ERROR "Input path not exist: " ${_path})
    endif()

    if(WIN32)
        set(minPathLen "3")
    else()
        set(minPathLen "1")
    endif()

    set(currPath ${_path})
    while(EXISTS ${currPath})
        message(STATUS "Checking path: " ${currPath})
        #find the file trunkToken file in each folder recursive
        if(EXISTS "${currPath}/trunkToken")
            set(VXL_TRUNK_DIR ${currPath})
            message(STATUS "Found trunk path: " ${currPath})
            break()
        else()
            string(FIND ${currPath} "/" index REVERSE)
            string(SUBSTRING ${currPath} "0" ${index} currPath)
        endif()        
        #check the string length
        string(LENGTH ${currPath} curPathLen)
        if(NOT(curPathLen GREATER minPathLen))
            message(FATAL_ERROR "Can not find the trunk path: " ${_path})
        endif()
    endwhile()
    unset(minPathLen CACHE)
    unset(curPathLen CACHE)
    unset(index CACHE)
endmacro()

