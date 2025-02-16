file(GLOB_RECURSE ARKAPONG_SOURCES "*.cpp")
file(GLOB_RECURSE ARKAPONG_HEADERS "*.h")

add_executable(ArkaPong ${ARKAPONG_SOURCES} ${ARKAPONG_HEADERS})

target_link_libraries(ArkaPong Core SDL2 SDL2main SDL2_mixer SDL2_ttf)
target_include_directories(ArkaPong PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET ArkaPong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:ArkaPong>/assets")

add_custom_command(TARGET ArkaPong POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/config.json"
    "$<TARGET_FILE_DIR:ArkaPong>/config.json")