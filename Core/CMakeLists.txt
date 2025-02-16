file(GLOB_RECURSE CORE_SOURCES "*.cpp")
file(GLOB_RECURSE CORE_HEADERS "*.h")

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(core SDL2 SDL2main SDL2_mixer SDL2_ttf)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Copy the config.json file to the output directory after the build.
add_custom_command(TARGET core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/config.json"
        "$<TARGET_FILE_DIR:core>/config.json")