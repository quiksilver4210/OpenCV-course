cmake_minimum_required(VERSION 3.14)
project(OpenCV_Course)

set(CMAKE_CXX_STANDARD 17)


macro(include_OpenCV TARGET)
    set(OpenCV_DIR "/home/quiks/installation/OpenCV-3.4.4/share/OpenCV/")
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${TARGET} ${OpenCV_LIBS})
endmacro()

add_subdirectory(1_capture)

add_subdirectory(2_color_correction)

add_subdirectory(3_filters)

add_subdirectory(4_contours)