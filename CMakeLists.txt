cmake_minimum_required(VERSION 3.15)

project(Origin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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

find_package(raylib REQUIRED)

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

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(origin PRIVATE
    nlohmann_json::nlohmann_json
)

find_package(fmt CONFIG REQUIRED)

target_link_libraries(origin PRIVATE 
    fmt::fmt-header-only
)
