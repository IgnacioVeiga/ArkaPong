cmake_policy(SET CMP0111 NEW)
cmake_minimum_required(VERSION 3.20)
project(ArkaPongGameEngine)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/_deps)

include(cmake/ThirdParty.cmake)

add_subdirectory(Core)
add_subdirectory(ArkaPong)
add_subdirectory(Frontend)
