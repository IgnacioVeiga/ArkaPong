file(GLOB_RECURSE CORE_SOURCES "*.cpp")
file(GLOB_RECURSE CORE_HEADERS "*.h")

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(core SDL2 SDL2main SDL2_mixer SDL2_ttf)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})