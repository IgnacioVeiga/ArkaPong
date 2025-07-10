cmake_minimum_required(VERSION 3.20)
project(ArkaPongGameEngine)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include(FetchContent)

if (WIN32)
    message(STATUS "Fetching SDL2 via FetchContent on Windows")

    FetchContent_Declare(
            SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.32.8
    )
    FetchContent_MakeAvailable(SDL2)

    FetchContent_Declare(
            SDL2_mixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
            GIT_TAG release-2.8.1
    )
    FetchContent_MakeAvailable(SDL2_mixer)

    FetchContent_Declare(
            SDL2_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-2.24.0
    )
    FetchContent_MakeAvailable(SDL2_ttf)

else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory(Core)
add_subdirectory(ArkaPong)
add_subdirectory(Frontend)
