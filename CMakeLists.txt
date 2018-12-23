#this file CMakeList.txt is used to build a solution,
#it should be put in the top level of a module
cmake_minimum_required(VERSION 3.5)
# ---------------------------------------------
#   1.set up solution name, it MUST be modified as required
# ---------------------------------------------
set(SOLUTION_NAME "VxlModules")

# ---------------------------------------------
#   2.check the define of variables
# ---------------------------------------------
#check trunk directory
set(VXL_TRUNK_DIR ${CMAKE_CURRENT_SOURCE_DIR})
if(EXISTS ${VXL_TRUNK_DIR})
    message(STATUS "VXL_TRUNK_DIR is definded: ${VXL_TRUNK_DIR}")
else()
    message(FATAL_ERROR "VXL_TRUNK_DIR is not definded!")
endif()

# ---------------------------------------------
#   3.global setting, set the name of the project
# ---------------------------------------------
#platform redefine
include(${VXL_TRUNK_DIR}/cmake/VxlUtils.cmake)
#create a new project(solution in VS)
project(${SOLUTION_NAME})
#set up compile flags
include(${VXL_TRUNK_DIR}/cmake/VxlUtilsPost.cmake)

# ---------------------------------------------
#   4.set path of public cmake modules
# ---------------------------------------------
set(CMAKE_MODULE_PATH ${VXL_TRUNK_DIR}/cmake)

# ---------------------------------------------
#   5.print basic information
# ---------------------------------------------
showSolutionInfo(${PROJECT_NAME})

# ---------------------------------------------
#   6.add subdirectory, it MUST be modified\added\removed as required
# ---------------------------------------------
add_subdirectory(modules)
add_subdirectory(test)

