# VxlCfgLibOpenCV3.cmake
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
#       include(${PATH_OF_THIS_FILE}/VxlCfgLibOpenCV3.cmake))
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

if(UNIX AND NOT APPLE)
    set(OPENCV3_PATH "D:/opencv343/opencv/build")
elseif(WIN32)
    if(NOT "${CMAKE_GENERATOR}" MATCHES "(Visual)")
        set(OPENCV3_PATH "D:/opencv343/opencv/build")
    else()
        set(OPENCV3_PATH "D:/opencv343/opencv/build")
    endif()
endif()

if(EXISTS ${OPENCV3_PATH})
    message(STATUS "OPENCV3_PATH:" ${OPENCV3_PATH})
else()
    message(FATAL_ERROR "ERROR:" ${OPENCV3_PATH} " not exist!!!")
endif()

find_package(OpenCV REQUIRED PATHS ${OPENCV3_PATH})

#      - OpenCV_LIBS                     : The list of libraries to link against.
#      - OpenCV_INCLUDE_DIRS             : The OpenCV include directories.
#      - OpenCV_COMPUTE_CAPABILITIES     : The version of compute capability
#      - OpenCV_SHARED
set(OPENCV_INCLUDES ${OpenCV_INCLUDE_DIRS})
set(OPENCV_LIB_DIR  ${OPENCV3_PATH})
set(OPENCV_LIBS_DBG ${OpenCV_LIBS})
set(OPENCV_LIBS_REL ${OpenCV_LIBS})

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