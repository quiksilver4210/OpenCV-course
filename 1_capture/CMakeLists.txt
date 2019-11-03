cmake_minimum_required(VERSION 3.14)
project(1_capture)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
include_OpenCV(${PROJECT_NAME})