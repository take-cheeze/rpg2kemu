CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT("rpg2kemu" CXX)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake_module
  ${CMAKE_CURRENT_SOURCE_DIR}/librpg2k/cmake_module)

# rpg2k things
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/librpg2k)
SET(rpg2k_PATH ${CMAKE_CURRENT_SOURCE_DIR}/librpg2k)
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/librpg2k/rpg2k.cmake)
INCLUDE_DIRECTORIES(${rpg2k_INCLUDE_DIRS})
ADD_DEFINITIONS(${rpg2k_DEFINITIONS})
LINK_DIRECTORIES(${rpg2k_LIBRARY_DIRS})

# output path
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# game code
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src SRCS)
ADD_EXECUTABLE(${PROJECT_NAME} MACOSX_BUNDLE ${SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${rpg2k_LIBRARIES})
ADD_DEPENDENCIES(${PROJECT_NAME} "rpg2k")

# packages
foreach(i Freetype SDL Pixman)
  find_package(${i} REQUIRED)
  include_directories(${${i}_INCLUDE_DIRS} ${${i}_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME}
    ${${i}_LIBRARIES} ${${i}_LIBRARY})
endforeach()

add_definitions(-DUSE_PIXMAN_BITMAP=1)

# precompiled header
#include(${rpg2k_PATH}/PrecompiledHeader.cmake)
#file(GLOB_RECURSE all_header "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx")
#create_precompiled_header(CXX
#  "${CMAKE_CURRENT_SOURCE_DIR}/include/all_header.pch" ${all_header})
#add_dependencies(${PROJECT_NAME} all_header.pch)
#precompiled_header_definition(
#  CXX pch_DEFINITIONS "${CMAKE_CURRENT_SOURCE_DIR}/include/all_header.pch")
#add_definitions(${pch_DEFINITIONS})

# test
ENABLE_TESTING()
