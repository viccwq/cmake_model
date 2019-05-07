# VxlCfgLibDlib.cmake
# ----------
#
# Try to find Dlib
#
# Once done this will define:
#   DLIB_FIND       - True if OpenCV was found
#   DLIB_INCLUDES   - include directories for OpenCV
#   DLIB_LIB_DIR    - library directories for OpenCV
#   DLIB_LIBS_DBG   - list all debug libraries for OpenCV
#   DLIB_LIBS_REL   - list all release libraries for OpenCV
#
# Usage from an external project:
#   In your CMakeLists.txt, add these lines:
#
#       include(${PATH_OF_THIS_FILE}/VxlCfgLibDlib.cmake))
#       include_directories(${DLIB_INCLUDES})
#       ...

#       target_link_libraries(${OBJ_NAME} debug ${DLIB_LIBS_REL})

#---------------------------------------------------------------------
#   1.set basic configuration for the 3rd party library, it should be 
#     modified as required
#---------------------------------------------------------------------
#set base directory, this path is offered to execute find_package command
include(${VXL_TRUNK_DIR}/cmake/VxlCfgVal.cmake)

#check the existance of the folder
if(EXISTS ${DLIB_PATH})
    message(STATUS "DLIB_PATH:" ${DLIB_PATH})
else()
    message(FATAL_ERROR "ERROR:" ${DLIB_PATH} " not exist!!!")
endif()

#set required version
set(DLIB_REQUIRED_VERSION 19.17.0 CACHE STRING "" FORCE)
#set other auxiliary variable 
set(DLIB_LIB_PREFIX "opencv_")

#---------------------------------------------------------------------
#   2.check the version of the library, it should be 
#     modified as required
#---------------------------------------------------------------------
#list the used libraries and find the package
find_package(dlib REQUIRED PATHS ${DLIB_PATH} NO_SYSTEM_ENVIRONMENT_PATH)

if(DLIB_REQUIRED_VERSION VERSION_EQUAL dlib_VERSION)
    message(STATUS "dlib version ${dlib_VERSION}")
else()
    message(FATAL_ERROR "dlib version ${dlib_VERSION} is not expected")
endif()

#      - dlib_LIBRARIES                : The list of all imported targets for dlib modules.
#      - dlib_INCLUDE_DIRS             : The dlib include directories.
#      - dlib_VERSION                  : The version of this dlib build.


set(DLIB_INCLUDES ${dlib_INCLUDE_DIRS})
set(DLIB_LIB_DIR  ${DLIB_PATH})
set(DLIB_LIBS_DBG ${dlib_LIBRARIES})
set(DLIB_LIBS_REL ${dlib_LIBRARIES})

message(STATUS "DLIB_INCLUDES: ${DLIB_INCLUDES}")
message(STATUS "DLIB_LIB_DIR:  ${DLIB_LIB_DIR}")
message(STATUS "DLIB_LIBS_DBG:")
foreach(_lib ${DLIB_LIBS_DBG})
    message(STATUS "    ${_lib}")
endforeach()
message(STATUS "DLIB_LIBS_REL:")
foreach(_lib ${DLIB_LIBS_REL})
    message(STATUS "    ${_lib}")
endforeach()
