cmake_minimum_required(VERSION 3.10)
project(ArkaPong VERSION 1.0)

# Encuentra las librerías SDL2, SDL2_ttf y SDL2_mixer
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Agrega los archivos fuente
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Agrega el ejecutable
add_executable(ArkaPong ${SOURCES})

# Enlaza las librerías SDL2, SDL2_ttf y SDL2_mixer
target_link_libraries(ArkaPong PRIVATE SDL2::Main SDL2::TTF SDL2::Mixer)

# Copiar recursos (imágenes, fuentes, sonidos, etc.) al directorio de compilación
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
