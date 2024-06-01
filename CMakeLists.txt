cmake_minimum_required(VERSION 3.10)
project(ArkaPong)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Required ".h" file folders
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Recursively adds all subdirectories containing headers
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.h")
foreach(_headerFile ${HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    include_directories(${_dir})
endforeach()

# Collect all ".cpp" files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Links SDL2 libraries to the project
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_mixer SDL2_ttf)

# TODO: Copy the necessary DLL files after the build (Windows ONLY)

# Copy the assets folder to where the executable is after the build.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
