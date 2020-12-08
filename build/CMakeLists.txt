cmake_minimum_required(VERSION 3.10)

project(plusplusplus_game)

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})
include_directories(${PARENT_DIR}/renderer)

file(GLOB SOURCES ../*.cpp)
file(GLOB RENDERER_SOURCES ../renderer/*.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wdelete-incomplete -Wenum-compare")

add_executable(game.out ${SOURCES} ${RENDERER_SOURCES})
target_compile_features(game.out PRIVATE cxx_std_17)
