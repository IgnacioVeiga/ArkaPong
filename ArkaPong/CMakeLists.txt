file(GLOB_RECURSE ARKAPONG_SOURCES "src/*.cpp")
file(GLOB_RECURSE ARKAPONG_HEADERS "src/*.h")

add_executable(ArkaPong ${ARKAPONG_SOURCES} ${ARKAPONG_HEADERS})

target_include_directories(ArkaPong
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/Core/include
        ${CMAKE_SOURCE_DIR}/Core/include/nlohmann-json
        ${SDL2_INCLUDE_DIR}
)

target_link_libraries(ArkaPong
        Core
        SDL2::SDL2 SDL2::SDL2main SDL2_mixer SDL2_ttf
)

add_custom_command(TARGET ArkaPong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ArkaPong/assets
        $<TARGET_FILE_DIR:ArkaPong>/assets

        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/ArkaPong/config.json
        $<TARGET_FILE_DIR:ArkaPong>/config.json
        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:ArkaPong>
        $<TARGET_FILE_DIR:ArkaPong>
    COMMAND_EXPAND_LISTS
)

set_target_properties(ArkaPong PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ArkaPong)
