file(GLOB_RECURSE ARKAPONG_SOURCES "*.cpp")
file(GLOB_RECURSE ARKAPONG_HEADERS "*.h")

add_executable(ArkaPong ${ARKAPONG_SOURCES} ${ARKAPONG_HEADERS})

target_link_libraries(ArkaPong core SDL2 SDL2main SDL2_mixer SDL2_ttf)
target_include_directories(ArkaPong PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Copy the assets folder to where the executable is after the build.
add_custom_command(TARGET ArkaPong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:ArkaPong>/assets")