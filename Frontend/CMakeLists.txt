file(GLOB_RECURSE FRONTEND_SOURCES "src/*.cpp")
file(GLOB_RECURSE FRONTEND_HEADERS "src/*.h")

add_executable(Frontend ${FRONTEND_SOURCES} ${FRONTEND_HEADERS})

# ImGui sources
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui-docking)
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

target_sources(Frontend PRIVATE ${IMGUI_SOURCES})

target_include_directories(Frontend
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${CMAKE_SOURCE_DIR}/Core/include
        ${CMAKE_SOURCE_DIR}/Core/include/nlohmann-json
        ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(Frontend
        Core
        SDL2 SDL2main SDL2_mixer SDL2_ttf
)

# (opcional) salida separada
set_target_properties(Frontend PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Frontend)
