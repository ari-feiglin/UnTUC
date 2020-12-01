cmake_minimum_required(VERSION 3.10)

project(UnTUC)

file(GLOB SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

message("${SOURCE}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_library(UnTUC SHARED ${SOURCE})