file(GLOB_RECURSE CORE_SOURCES "src/Core.cpp" "src/**/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "include/Core/**/*.h")

add_library(Core STATIC ${CORE_SOURCES} ${CORE_HEADERS})

target_include_directories(Core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIR}
)

target_link_libraries(Core
        SDL2::SDL2 SDL2::SDL2main SDL2_mixer SDL2_ttf
)

add_custom_command(TARGET Core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Core> ${CMAKE_SOURCE_DIR}/ArkaPong/lib/
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Core> ${CMAKE_SOURCE_DIR}/Frontend/lib/
)
