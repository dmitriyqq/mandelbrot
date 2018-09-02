cmake_minimum_required(VERSION 3.10)
project(Mandelbrot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
add_executable(Mandelbrot src.cpp SFMLDebug.h SFMLDebug.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(Mandelbrot sfml-graphics sfml-system sfml-window)
