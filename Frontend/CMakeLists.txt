cmake_policy(SET CMP0111 NEW)
cmake_minimum_required(VERSION 3.20)
project(Frontend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Frontend)

# Incluir script local de terceros (SDL2). Buscar primero en cmake/, si no existe usar ../cmake/ como fallback.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ThirdParty.cmake")
        include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ThirdParty.cmake")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ThirdParty.cmake")
        include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ThirdParty.cmake")
else()
        message(WARNING "ThirdParty.cmake no encontrado en ${CMAKE_CURRENT_SOURCE_DIR}/cmake ni ../cmake. SDL2 puede no estar disponible.")
endif()

# Core se distribuye como biblioteca portable. El usuario debe proporcionar las rutas a headers/lib
# Opciones esperadas (opcional):
#  -DCORE_INCLUDE_DIR=/path/to/Core/include
#  -DCORE_LIBRARY=/path/to/libCore.so (o .dll/.a según plataforma)
if(NOT DEFINED CORE_INCLUDE_DIR)
        set(CORE_INCLUDE_DIR "")
endif()
if(NOT DEFINED CORE_LIBRARY)
        set(CORE_LIBRARY "")
endif()

file(GLOB_RECURSE FRONTEND_SOURCES "src/*.cpp")
file(GLOB_RECURSE FRONTEND_HEADERS "src/*.h")

add_executable(Frontend ${FRONTEND_SOURCES} ${FRONTEND_HEADERS})

# ImGui
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
        $<$<BOOL:${CORE_INCLUDE_DIR}>:${CORE_INCLUDE_DIR}>
        ${SDL2_INCLUDE_DIR}
)

target_link_libraries(Frontend
        ${CORE_LIBRARY}
        SDL2::SDL2 SDL2::SDL2main SDL2_mixer SDL2_ttf
)

if(WIN32)
    add_custom_command(TARGET Frontend POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:Frontend>
            $<TARGET_FILE_DIR:Frontend>
            COMMAND_EXPAND_LISTS
    )
endif()

# Copy ThirdParty.cmake to cmake directory if it doesn't exist
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ThirdParty.cmake")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ThirdParty.cmake" 
         DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
endif()
