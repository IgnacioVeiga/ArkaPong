cmake_policy(SET CMP0111 NEW)
cmake_minimum_required(VERSION 3.20)
project(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include a local third-party script (SDL2).
include("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty.cmake")

file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "include/Core/**/*.h")

add_library(Core SHARED ${CORE_SOURCES} ${CORE_HEADERS})

target_include_directories(Core
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Core
        PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_mixer SDL2_ttf
)

if (WIN32)
    target_compile_definitions(Core PRIVATE CORE_BUILD_DLL)
endif()

# Install and export targets
include(GNUInstallDirs)
# Note: Core is a portable library. No targets are installed or exported in this CMake.
# The user will need to manually copy the library and headers to the projects that consume it.
