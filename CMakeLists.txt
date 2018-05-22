cmake_minimum_required (VERSION 2.6)
project (Tutorial)
include(CheckFunctionExists)



include_directories ("./common/")

file(GLOB SOURCES "common/*.c")

add_executable(out exercise3/main.c ${SOURCES})
target_link_libraries(out m)
