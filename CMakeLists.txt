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
# Build libzip submodule
# URL:
add_subdirectory(external/libzippp)

###################################################################
# Build toml11 submodule
# URL: 
set(toml11_BUILD_TEST OFF)
add_subdirectory(external/toml11)

###################################################################
# Build spdlog submodule
# URL: 
add_subdirectory(external/spdlog)

###################################################################
# Build EntityX submodule
# URL: https://github.com/alecthomas/entityx.git
set(ENTITYX_BUILD_TESTING OFF)
add_subdirectory(external/EntityX)

###################################################################
# Build entt submodule
# URL: https://github.com/skypjack/entt.git
set(USE_LIBCPP OFF)
add_subdirectory(external/entt)

###################################################################
# Build Eigen submodule
# URL: https://github.com/eigenteam/eigen-git-mirror.git
set(BUILD_TESTING OFF)
add_subdirectory(external/Eigen)

###################################################################
# Graphic Library
file(GLOB_RECURSE GRAPHIC_SRC src/Graphic/*.cpp)
add_library(graphic STATIC ${GRAPHIC_SRC})
target_include_directories(graphic PRIVATE "src/Graphic" src/Graphic/ResourceManager)
target_link_libraries(graphic PUBLIC sfml-window sfml-graphics EnTT eigen spdlog::spdlog libzippp zip toml11::toml11)

###################################################################
# Engine Library
file(GLOB ENGINE_SRC src/Engine/*.cpp)
add_library(engine STATIC ${ENGINE_SRC})
target_include_directories(engine PRIVATE src/Engine)
target_link_libraries(engine PUBLIC EnTT eigen)

###################################################################
# Snakepp Executable
file(GLOB SNAKEPP_SRC src/*.cpp)
add_executable(snakepp ${SNAKEPP_SRC})
target_link_libraries(snakepp PUBLIC engine graphic)