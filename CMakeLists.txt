# Establecer la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(ArkaPong)

# Especificar el estándar de C++ requerido
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Definir el directorio de salida para los ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Incluye las carpetas de encabezados necesarias
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Añadir recursivamente todos los subdirectorios que contienen headers
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.h")
foreach(_headerFile ${HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    include_directories(${_dir})
endforeach()

# Añadir directorio donde están los archivos de las librerías de SDL
# link_directories(${CMAKE_SOURCE_DIR}/lib)

# Recopilar todos los archivos fuente .cpp
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crear el ejecutable con base en los fuentes encontrados
add_executable(${PROJECT_NAME} ${SOURCES})

# Vincular las bibliotecas de SDL2 al proyecto
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_mixer SDL2_ttf)

# Copiar los archivos DLL y recursos necesarios después de la construcción
# Copia todos los archivos .dll
# file(GLOB DLL_FILES "${PROJECT_SOURCE_DIR}/lib/*.dll")
# foreach(dll ${DLL_FILES})
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${dll}
#         "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
# endforeach()


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
