cmake_minimum_required(VERSION 3.16)
project(ThermalApp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(thermal_app
    src/main.cpp
    src/frame_io.cpp
    src/display.cpp
    src/processor.cpp
    src/bad_pixel.cpp
    src/overlay.cpp
)
target_link_libraries(thermal_app ${OpenCV_LIBS} stdc++fs)
