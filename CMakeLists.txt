cmake_minimum_required(VERSION 3.15)

project(raylib_test VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(raylib REQUIRED)

add_executable(origin
    src/main.cpp
    src/characters/abstract/entity.cpp
    src/world/tile.cpp
)

set_target_properties(origin PROPERTIES
    WIN32_EXECUTABLE $<$<CONFIG:Release>:TRUE>
)

target_include_directories(origin PRIVATE
    src
    src/characters/abstract
    src/configuration
    src/configuration/world
    src/configuration/sprites
    src/world
)

target_link_libraries(origin PRIVATE 
    raylib
    winmm.lib
    gdi32.lib
    user32.lib
    shell32.lib
)

target_link_libraries(origin PRIVATE 
    raylib
)
