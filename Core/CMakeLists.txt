cmake_policy(SET CMP0111 NEW)
cmake_minimum_required(VERSION 3.20)
project(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Buscar ThirdParty.cmake en el propio proyecto primero, si no existe, usar el del repo padre
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ThirdParty.cmake")
        include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ThirdParty.cmake")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ThirdParty.cmake")
        include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ThirdParty.cmake")
else()
        message(WARNING "ThirdParty.cmake no encontrado en ${CMAKE_CURRENT_SOURCE_DIR}/cmake ni en ../cmake. Manejo de SDL2 puede fallar.")
endif()

file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "include/Core/**/*.h")

add_library(Core SHARED ${CORE_SOURCES} ${CORE_HEADERS})

target_include_directories(Core
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Core
        PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_mixer SDL2_ttf
)

if (WIN32)
    target_compile_definitions(Core PRIVATE CORE_BUILD_DLL)
endif()

# Copy ThirdParty.cmake to cmake directory if it doesn't exist
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ThirdParty.cmake")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ThirdParty.cmake" 
         DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
endif()

# Install and export targets
include(GNUInstallDirs)
# Nota: Core es una biblioteca portable. No se instalan ni exportan targets en este CMake.
# El usuario deberá copiar manualmente la librería y los headers a los proyectos que la consuman.
