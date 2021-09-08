cmake_minimum_required(VERSION 3.20)
project(sprites)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(./include /usr/include)
link_directories(/usr/lib)
link_libraries(-lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window pthread)

add_executable(
    a.out

    src/main.cpp
    src/dino.cpp

    include/dino.hpp
)

