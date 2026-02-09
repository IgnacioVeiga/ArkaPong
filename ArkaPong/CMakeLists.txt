cmake_policy(SET CMP0111 NEW)
cmake_minimum_required(VERSION 3.20)
project(ArkaPong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ArkaPong)

# Include a local third-party script (SDL2).
include("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty.cmake")

# Core is distributed as a portable library. The user must provide the paths to headers/lib
# Expected options (optional):
#  -DCORE_INCLUDE_DIR=/path/to/Core/include
#  -DCORE_LIBRARY=/path/to/libCore.so (or .dll/.a depending on platform)
if(NOT DEFINED CORE_INCLUDE_DIR)
        set(CORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core_local/include")
endif()
if(NOT DEFINED CORE_LIBRARY)
        set(_core_candidates
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/Core.lib"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.lib"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/Core.dll"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.so"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.dylib"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.a"
        )
        foreach(_core_candidate IN LISTS _core_candidates)
                if(EXISTS "${_core_candidate}")
                        set(CORE_LIBRARY "${_core_candidate}")
                        break()
                endif()
        endforeach()
        unset(_core_candidate)
        unset(_core_candidates)
endif()

if(NOT DEFINED CORE_LIBRARY)
        set(CORE_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.so")
endif()

file(GLOB_RECURSE ARKAPONG_SOURCES "src/*.cpp")
file(GLOB_RECURSE ARKAPONG_HEADERS "src/*.h")

add_executable(ArkaPong ${ARKAPONG_SOURCES} ${ARKAPONG_HEADERS})

target_include_directories(ArkaPong
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CORE_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
)

target_link_libraries(ArkaPong
        ${CORE_LIBRARY}
        SDL2::SDL2 SDL2::SDL2main SDL2_mixer SDL2_ttf
)

add_custom_command(TARGET ArkaPong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ArkaPong>/assets
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/config.json
        $<TARGET_FILE_DIR:ArkaPong>/config.json
)

if(WIN32)
    add_custom_command(TARGET ArkaPong POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:ArkaPong>
            $<TARGET_FILE_DIR:ArkaPong>
            COMMAND_EXPAND_LISTS
    )
endif()
