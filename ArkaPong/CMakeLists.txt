file(GLOB_RECURSE ARKAPONG_SOURCES "src/*.cpp")
file(GLOB_RECURSE ARKAPONG_HEADERS "src/*.h")

add_executable(ArkaPong ${ARKAPONG_SOURCES} ${ARKAPONG_HEADERS})

target_include_directories(ArkaPong
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/Core/include
        ${CMAKE_SOURCE_DIR}/Core/include/nlohmann-json
)

target_link_libraries(ArkaPong
        Core
        SDL2 SDL2main SDL2_mixer SDL2_ttf
)

# Copiar assets y config.json al ejecutable
add_custom_command(TARGET ArkaPong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ArkaPong>/assets
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config.json
        $<TARGET_FILE_DIR:ArkaPong>/config.json
)

# (opcional) salida separada
set_target_properties(ArkaPong PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ArkaPong)
