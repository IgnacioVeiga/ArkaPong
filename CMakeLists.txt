cmake_minimum_required(VERSION 3.10)
project(ArkaPongGameEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# Set the base directory for FetchContent downloads
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/ThirdParty)

# Try to find SDL2, SDL2_mixer, SDL2_ttf in the normal way
find_package(SDL2 QUIET)
find_package(SDL2_mixer QUIET)
find_package(SDL2_ttf QUIET)

# If they are not found, use FetchContent to download them
if(NOT SDL2_FOUND OR NOT SDL2_MIXER_FOUND OR NOT SDL2_TTF_FOUND)
    message(STATUS "SDL2 libraries not found, downloading with FetchContent...")

    if(NOT SDL2_FOUND)
        FetchContent_Declare(
            SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.30.8
        )
        FetchContent_MakeAvailable(SDL2)
    endif()

    if(NOT SDL2_mixer_FOUND)
        FetchContent_Declare(
            SDL2_mixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
            GIT_TAG release-2.8.0
        )
        FetchContent_MakeAvailable(SDL2_mixer)
    endif()

    if(NOT SDL2_ttf_FOUND)
        FetchContent_Declare(
            SDL2_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-2.22.0
        )
        FetchContent_MakeAvailable(SDL2_ttf)
    endif()

    # Set the include directories
    set(SDL2_INCLUDE_DIRS ${sdl2_SOURCE_DIR}/include)
    set(SDL2_MIXER_INCLUDE_DIRS ${sdl2_mixer_SOURCE_DIR}/include)
    set(SDL2_TTF_INCLUDE_DIRS ${sdl2_ttf_SOURCE_DIR}/include)
endif()

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Add subdirectories
add_subdirectory(Core)
add_subdirectory(ArkaPong)
add_subdirectory(Frontend)
