#this file CMakeList.txt is used to build a solution,
#it should be put in the top level of a module
cmake_minimum_required(VERSION 3.5)
# ---------------------------------------------
#   1.set up solution name, it MUST be modified as required
# ---------------------------------------------
set(SOLUTION_NAME "tmvDetectPyrStatic")

# ---------------------------------------------
#   2.check the define of variables
# ---------------------------------------------
#check trunk directory
if(EXISTS ${VCA_TRUNK_DIR})
    message(STATUS "VCA_TRUNK_DIR is definded: ${VCA_TRUNK_DIR}")
else()
    message(FATAL_ERROR "VCA_TRUNK_DIR is not definded:")
endif()

# ---------------------------------------------
#   3.global setting, set the name of the project
# ---------------------------------------------
#platform redefine
include(${VCA_TRUNK_DIR}/src/cmake/VcaUtils.cmake)
#create a new project(solution in VS)
project(${SOLUTION_NAME})
#set up compile flags
include(${VCA_TRUNK_DIR}/src/cmake/VcaUtilsPost.cmake)

# ---------------------------------------------
#   4.set path of public cmake modules
# ---------------------------------------------
set(CMAKE_MODULE_PATH ${VCA_TRUNK_DIR}/src/cmake)

# ---------------------------------------------
#   5.print basic information
# ---------------------------------------------
showSolutionInfo(${PROJECT_NAME})

# ---------------------------------------------
#   6.add subdirectory, it MUST be modified\added\removed as required
# ---------------------------------------------
add_subdirectory(cmake)
add_subdirectory(test/cmake)
