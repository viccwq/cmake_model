# VxlCfgLibOpenCV.cmake
# ----------
#
# Try to find OpenCV
#
# Once done this will define:
#   OPENCV_FIND       - True if OpenCV was found
#   OPENCV_INCLUDES   - include directories for OpenCV
#   OPENCV_LIB_DIR    - library directories for OpenCV
#   OPENCV_LIBS_DBG   - list all debug libraries for OpenCV
#   OPENCV_LIBS_REL   - list all release libraries for OpenCV
#
# Usage from an external project:
#   In your CMakeLists.txt, add these lines:
#
#       #set "OPENCV_LIB_LIST_EX" is optional, this used the specify 
#       #the library by users. when it is commented, system will using
#       #default libraries, including(core imgproc highgui calib3d)
#       set(OPENCV_LIB_LIST_EX core imgproc highgui)
#       #include the cmake script to generate related variables mentioned
#       #above
#       include(${PATH_OF_THIS_FILE}/VxlCfgLibOpenCV.cmake))
#       include_directories(${OPENCV_INCLUDES})
#       link_directories(${OPENCV_LIB_DIR})
#       ...
#       foreach(_lib ${OPENCV_LIBS_DBG})
#           target_link_libraries(${OBJ_NAME} debug ${_lib})
#       endforeach()
#
#       foreach(_lib ${OPENCV_LIBS_REL})
#           target_link_libraries(${OBJ_NAME} optimized ${_lib})
#       endforeach()

#---------------------------------------------------------------------
#   1.set basic configuration for the 3rd party library, it should be 
#     modified as required
#---------------------------------------------------------------------
#set base directory, this path is offered to execute find_package command
if(WIN32)
    set(OpenCV_DIR D:/opencv/gpu/install CACHE STRING "" FORCE)
elseif(UNIX)
    set(OpenCV_DIR /usr/local/share/OpenCV CACHE STRING "" FORCE)
else()
endif()
#set required version
set(OpenCV_REQUIRED_VERSION 2.4.9 CACHE STRING "" FORCE)
#set other auxiliary variable 
set(OpenCV_LIB_PREFIX "opencv_")
#list the used libraries
if(DEFINED OPENCV_LIB_LIST_EX)
    message(STATUS "Using user defined OPENCV_LIB_LIST")
    set(OpenCV_LIB_LIST  ${OPENCV_LIB_LIST_EX} CACHE STRING "" FORCE)
else()
    message(STATUS "Using default OPENCV_LIB_LIST")
    set(OpenCV_LIB_LIST  core imgproc highgui calib3d CACHE STRING "" FORCE)
endif()

#---------------------------------------------------------------------
#   2.check the version of the library, it should be 
#     modified as required
#---------------------------------------------------------------------
if(EXISTS ${OpenCV_DIR})
    include(${OpenCV_DIR}/OpenCVConfig-version.cmake)
else()
    message(FATAL_ERROR "OpenCV_DIR ${OpenCV_DIR} is not exists")
endif()

if(OpenCV_REQUIRED_VERSION VERSION_EQUAL OpenCV_VERSION)
    message(STATUS "OpenCV version ${OpenCV_VERSION}")
else()
    message(FATAL_ERROR "OpenCV version ${OpenCV_VERSION} is not expected")  
endif()

#---------------------------------------------------------------------
#   3.find the include directory of the library, set the include path to
#     "XXXX_INCLUDS"; 
#     find the library directory of the library, set the library path to
#     "XXXX_LIB_DIR";
#     find all the required libraries listed in "OpenCV_LIB_LIST", set the
#     library list to "XXXX_LIBS", note that the library's name should be
#     renamed according different requirement;
#
#     NOTE: all the above actions should should take the operation system
#           ARCH and the compiler's version into account
#---------------------------------------------------------------------
if(WIN32)
    #set include directory
    set(OPENCV_INCLUDES "${OpenCV_DIR}/include")
    #check OS ARCH
    if(WIN_X64)
        set(CV_PLATFORM "x64")
    elseif(WIN_X86)
        set(CV_PLATFORM "x86")
    else()
        message(FATAL_ERROR "Could not find correct platform")
    endif()
    
    #check compiler version
    if(MSVC_VERSION EQUAL 1400)
        set(CV_RUNTIME vc8)
    elseif(MSVC_VERSION EQUAL 1500)
        set(CV_RUNTIME vc9)
    elseif(MSVC_VERSION EQUAL 1600)
        set(CV_RUNTIME vc10)
    elseif(MSVC_VERSION EQUAL 1700)
        set(CV_RUNTIME vc11)
    elseif(MSVC_VERSION EQUAL 1800)
        set(CV_RUNTIME vc12)
    endif()
    
    #set library directory
    set(OPENCV_LIB_DIR "${OpenCV_DIR}/${CV_PLATFORM}/${CV_RUNTIME}/lib")
    if((EXISTS ${OPENCV_INCLUDES}) AND (EXISTS ${OPENCV_LIB_DIR}))
       set(OPENCV_FIND TRUE)
       message(STATUS "Found OpenCV")
    else()
       message(FATAL_ERROR "Could not find OpenCV library")
    endif()
    
    #rename library list
    string(REPLACE "." "" _suffixVer ${OpenCV_VERSION})

    set(OPENCV_LIBS_DBG "")
    set(OPENCV_LIBS_REL "")
    foreach(_lib ${OpenCV_LIB_LIST})
        list(APPEND OPENCV_LIBS_DBG ${OpenCV_LIB_PREFIX}${_lib}${_suffixVer}d.lib)
        list(APPEND OPENCV_LIBS_REL ${OpenCV_LIB_PREFIX}${_lib}${_suffixVer}.lib)
    endforeach()
elseif(UNIX)
    #set include directory
    set(OPENCV_INCLUDES "/usr/local/include")
    #set library directory
    find_path(OPENCV_LIB_DIR "libopencv_core.so" PATHS "/usr/local/lib")

    if((EXISTS ${OPENCV_INCLUDES}) AND (EXISTS ${OPENCV_LIB_DIR}))
       set(OPENCV_FIND TRUE)
       message(STATUS "Found OpenCV")
    else()
       message(FATAL_ERROR "Could not find OpenCV library")
    endif()

    #rename library list
    set(OPENCV_LIBS_DBG "")
    set(OPENCV_LIBS_REL "")
    foreach(_lib ${OpenCV_LIB_LIST})
        list(APPEND OPENCV_LIBS_DBG ${OpenCV_LIB_PREFIX}${_lib})
        list(APPEND OPENCV_LIBS_REL ${OpenCV_LIB_PREFIX}${_lib})
    endforeach()
else()
    message(STATUS "unknown environment")
endif()

message(STATUS "OPENCV_INCLUDES: ${OPENCV_INCLUDES}")
message(STATUS "OPENCV_LIB_DIR:  ${OPENCV_LIB_DIR}")
message(STATUS "OPENCV_LIBS_DBG:")
foreach(_lib ${OPENCV_LIBS_DBG})
    message(STATUS "    ${_lib}")
endforeach()
message(STATUS "OPENCV_LIBS_REL:")
foreach(_lib ${OPENCV_LIBS_REL})
    message(STATUS "    ${_lib}")
endforeach()