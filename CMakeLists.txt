cmake_minimum_required(VERSION 3.10)
project(SDL2_Image_Starter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

file(COPY images DESTINATION ${CMAKE_BINARY_DIR})

add_executable(SDL2_Image_Starter main.cpp Game.cpp Game.h)
target_link_libraries(SDL2_Image_Starter ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})