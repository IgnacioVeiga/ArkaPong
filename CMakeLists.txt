# Establecer la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Pong VERSION 1.0)

# Especificar el estándar de C++ requerido
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir directorios donde están los headers
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Añadir recursivamente todos los subdirectorios que contienen headers
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.h")
foreach(_headerFile ${HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    include_directories(${_dir})
endforeach()

# Añadir directorio donde están los archivos de las librerías de SDL
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Recopilar todos los archivos fuente .cpp
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crear el ejecutable con base en los fuentes encontrados
add_executable(${PROJECT_NAME} ${SOURCES})

# Vincular las bibliotecas de SDL2 al proyecto
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_mixer SDL2_ttf)

# Copia SDL2.dll
add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/lib/SDL2.dll"
    "$<TARGET_FILE_DIR:Pong>")

# Copia SDL2_mixer.dll
add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer.dll"
    "$<TARGET_FILE_DIR:Pong>")

# Copia SDL2_ttf.dll
add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/lib/SDL2_ttf.dll"
    "$<TARGET_FILE_DIR:Pong>")

add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:Pong>/assets")

# (Opcional) Define las rutas de los DLL para ejecución en Windows
if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/SDL2.dll"
        "${CMAKE_BINARY_DIR}/bin")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/SDL2_mixer.dll"
        "${CMAKE_BINARY_DIR}/bin")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/SDL2_ttf.dll"
        "${CMAKE_BINARY_DIR}/bin")
endif()
