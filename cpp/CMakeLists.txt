cmake_minimum_required(VERSION 3.16)
project(ThermalApp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(thermal_app src/main.cpp)
target_link_libraries(thermal_app ${OpenCV_LIBS} stdc++fs)
