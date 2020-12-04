cmake_minimum_required(VERSION 3.10)

project(plusplusplus_test)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

file(GLOB TEST_SOURCES ./*.cpp)
file(GLOB SOURCES ../*.cpp)
file(GLOB RENDERER_SOURCES ../renderer/*.cpp)

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp")

add_executable(tests ${TEST_SOURCES} ${SOURCES} ${RENDERER_SOURCES})
target_compile_features(tests PRIVATE cxx_std_17)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)