cmake_minimum_required(VERSION 3.0)
project(SNAKEPP)

###################################################################
# General Setting

# configure general include
include_directories(src/)

# configure compiler command
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 ")

###################################################################
# Build SFML submodule
# URL: https://github.com/SFML/SFML.git
add_subdirectory(external/SFML)

###################################################################
# Build EntityX submodule
# URL: https://github.com/alecthomas/entityx.git
set(ENTITYX_BUILD_TESTING OFF)
add_subdirectory(external/EntityX)

###################################################################
# Build Eigen submodule
# URL: https://github.com/eigenteam/eigen-git-mirror.git
set(BUILD_TESTING OFF)
add_subdirectory(external/Eigen)

###################################################################
# Snakepp Executable
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 ")
file(GLOB_RECURSE SNAKEPP_SRC src/*.cpp)
add_library(snakepp ${SNAKEPP_SRC})
target_link_libraries(snakepp PUBLIC sfml-window sfml-graphics entityx eigen)