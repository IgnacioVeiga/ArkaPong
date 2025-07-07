cmake_minimum_required(VERSION 3.20)
project(ArkaPongGameEngine)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SDL2 buscar en el sistema
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

#message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")

# Subproyectos
add_subdirectory(Core)
add_subdirectory(ArkaPong)
add_subdirectory(Frontend)
