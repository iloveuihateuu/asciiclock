cmake_minimum_required(VERSION 3.23)
project(asciiclock LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(asciiclock
    src/main.cpp 
    src/renderer.cpp 
    src/shapes.cpp 
    src/clock.cpp 
    src/input.cpp 
    src/surface.cpp 
    src/interface.cpp
)

target_link_libraries(asciiclock
    ncursesw
    panel
    menu
)
