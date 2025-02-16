cmake_minimum_required(VERSION 3.10)
project(ArkaPongGameEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Try to find SDL2, SDL2_mixer, SDL2_ttf in the normal way
find_package(SDL2 QUIET)
find_package(SDL2_mixer QUIET)
find_package(SDL2_ttf QUIET)

# If they are not found, use vcpkg
if(NOT SDL2_FOUND OR NOT SDL2_MIXER_FOUND OR NOT SDL2_TTF_FOUND)
    message(STATUS "SDL2 libraries not found, trying with vcpkg...")
    
    # Try using environment variable VCPKG_ROOT
    if(DEFINED ENV{VCPKG_ROOT})
        message(STATUS "Using vcpkg from environment variable VCPKG_ROOT: $ENV{VCPKG_ROOT}")
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to vcpkg toolchain file")
    else()
        # Use default routes if VCPKG_ROOT is not set
        if(WIN32)
            set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to vcpkg toolchain file")
        else()
            set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to vcpkg toolchain file")
        endif()
    endif()

    
    # Trying to find the libraries again after configuring vcpkg
    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
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
