file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "include/Core/**/*.h")

add_library(Core SHARED ${CORE_SOURCES} ${CORE_HEADERS})

target_include_directories(Core
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Core
        PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_mixer SDL2_ttf
)

if (WIN32)
    target_compile_definitions(Core PRIVATE CORE_BUILD_DLL)
endif()
