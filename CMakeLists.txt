cmake_minimum_required(VERSION 3.15)

project(raylib_test VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(raylib REQUIRED)

add_executable(rayLibTest
    src/main.cpp
    src/characters/abstract/game_character.cpp
)

set_target_properties(rayLibTest PROPERTIES
    WIN32_EXECUTABLE $<$<CONFIG:Release>:TRUE>
)

target_include_directories(rayLibTest PRIVATE
    src
    src/characters/abstract
    src/configuration
    src/configuration/world
)

target_link_libraries(rayLibTest PRIVATE 
    raylib
    winmm.lib
    gdi32.lib
    user32.lib
    shell32.lib
)

# Only link raylib. vcpkg's raylib target brings its own GLFW and Win32 system libs!
target_link_libraries(rayLibTest PRIVATE 
    raylib
)
