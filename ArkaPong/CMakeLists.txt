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
#  -DCORE_LIBRARY=/path/to/Core binary used for linking (.lib/.so/.dylib/.a)
#  -DCORE_RUNTIME_DLLS=/path/to/Core.dll (Windows runtime copy)
if(NOT DEFINED CORE_INCLUDE_DIR)
        set(CORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core_local/include")
endif()
if(NOT DEFINED CORE_LIBRARY)
        set(_core_candidates
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/Core.lib"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.lib"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.so"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.dylib"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/libCore.a"
                "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/Core.dll"
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

if(WIN32 AND NOT DEFINED CORE_RUNTIME_DLLS)
        if(DEFINED CORE_LIBRARY)
                get_filename_component(_core_lib_dir "${CORE_LIBRARY}" DIRECTORY)
                set(_core_runtime_candidates
                        "${_core_lib_dir}/Core.dll"
                        "${_core_lib_dir}/libCore.dll"
                        "${_core_lib_dir}/../bin/Core.dll"
                        "${_core_lib_dir}/../bin/libCore.dll"
                )
        else()
                set(_core_runtime_candidates
                        "${CMAKE_CURRENT_SOURCE_DIR}/core_local/lib/Core.dll"
                        "${CMAKE_CURRENT_SOURCE_DIR}/core_local/bin/Core.dll"
                )
        endif()

        foreach(_core_runtime_candidate IN LISTS _core_runtime_candidates)
                if(EXISTS "${_core_runtime_candidate}")
                        list(APPEND CORE_RUNTIME_DLLS "${_core_runtime_candidate}")
                endif()
        endforeach()
        list(REMOVE_DUPLICATES CORE_RUNTIME_DLLS)
        unset(_core_runtime_candidate)
        unset(_core_runtime_candidates)
endif()

if(NOT DEFINED CORE_LIBRARY)
        message(WARNING "Core library not found. Populate ArkaPong/core_local or pass -DCORE_LIBRARY explicitly.")
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

    if(CORE_RUNTIME_DLLS)
        add_custom_command(TARGET ArkaPong POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CORE_RUNTIME_DLLS}
                $<TARGET_FILE_DIR:ArkaPong>
                COMMAND_EXPAND_LISTS
        )
    endif()
endif()
