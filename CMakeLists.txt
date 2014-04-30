cmake_minimum_required(VERSION 2.8)
project(Svit)

file(GLOB_RECURSE Svit_SOURCES "src/*.cpp")
file(GLOB_RECURSE Svit_HEADERS "src/*.h")

include_directories("src/")

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -O3 ")
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
add_executable (Svit ${Svit_SOURCES})
target_link_libraries(Svit ${PNG_LIBRARY})

