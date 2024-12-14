#TODO: Make file for windows platform to build
cmake_minimum_required(VERSION 3.25)
project(3d_renderer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_OSX_ARCHITECTURES "arm64")

include_directories(/opt/homebrew/include/SDL2)
link_directories(/opt/homebrew/lib)

add_executable(renderer ./src/main.c src/display.h src/display.h src/display.c src/math/vector.c)

target_link_libraries(renderer SDL2)