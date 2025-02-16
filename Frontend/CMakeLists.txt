file(GLOB_RECURSE FRONTEND_SOURCES "*.cpp")
file(GLOB_RECURSE FRONTEND_HEADERS "*.h")

add_executable(frontend ${FRONTEND_SOURCES} ${FRONTEND_HEADERS})

target_link_libraries(frontend core SDL2 SDL2main)
target_include_directories(frontend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui-docking ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui-docking/backends)