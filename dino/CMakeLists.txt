cmake_minimum_required(VERSION 3.20)
project(dino)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(./include /usr/include)
link_directories(/usr/lib)
link_libraries(-lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window pthread)

add_executable(
    a.out

    src/main.cpp
    src/textures.cpp
    src/game.cpp
    src/dino.cpp
    src/enemy.cpp
    src/window.cpp
    src/ground.cpp
    src/text.cpp

    include/util.hpp
    include/textures.hpp
    include/game.hpp
    include/dino.hpp
    include/enemy.hpp
    include/window.hpp
    include/ground.hpp
    include/text.hpp
    include/sky.hpp src/sky.cpp)

