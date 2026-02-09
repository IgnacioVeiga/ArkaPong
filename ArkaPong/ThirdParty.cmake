# Copia local de ThirdParty.cmake para ArkaPong
# ==========================================
# ThirdParty.cmake — SDL2 dependency handler
# Priority: 1) Local  2) System  3) FetchContent
# ==========================================

include(FetchContent)

# Base path for local third-party libraries
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/ThirdParty")

# ------------------------------------------
# Helper macro to define a local imported library
# ------------------------------------------
macro(import_local_lib NAME LIB_NAME FOUND_VAR)
    set(LIB_DIR "${THIRDPARTY_DIR}/${LIB_NAME}")

    if (EXISTS "${LIB_DIR}/include" AND EXISTS "${LIB_DIR}/lib")
        message(STATUS "Using local ${NAME} from ${LIB_DIR}")

        add_library(${NAME} SHARED IMPORTED)

        if (WIN32)
            set_target_properties(${NAME} PROPERTIES
                    IMPORTED_LOCATION "${LIB_DIR}/lib/${LIB_NAME}.dll"
                    IMPORTED_IMPLIB "${LIB_DIR}/lib/${LIB_NAME}.lib"
            )

        elseif (UNIX)
            set_target_properties(${NAME} PROPERTIES
                    IMPORTED_LOCATION "${LIB_DIR}/lib/lib${LIB_NAME}.so"
            )
        endif()

        set_target_properties(${NAME} PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${LIB_DIR}/include"
        )

        set(${FOUND_VAR} TRUE)
    endif()
endmacro()

# ------------------------------------------
# SDL2
# ------------------------------------------
set(SDL2_FOUND FALSE)
import_local_lib(SDL2::SDL2 SDL2 SDL2_FOUND)

if (NOT SDL2_FOUND)
    find_package(SDL2 QUIET)
    if (SDL2_FOUND)
        message(STATUS "Using system-installed SDL2.")
    else()
        message(WARNING "SDL2 not found locally or in system. Using FetchContent...")
        FetchContent_Declare(
                SDL2
                GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
                GIT_TAG release-2.32.8
        )
        FetchContent_MakeAvailable(SDL2)
    endif()
endif()

# ------------------------------------------
# SDL2_mixer
# ------------------------------------------
set(SDL2_mixer_FOUND FALSE)
import_local_lib(SDL2_mixer SDL2_mixer SDL2_mixer_FOUND)

if (NOT SDL2_mixer_FOUND)
    find_package(SDL2_mixer QUIET)
    if (SDL2_mixer_FOUND)
        message(STATUS "Using system-installed SDL2_mixer.")
    else()
        message(WARNING "SDL2_mixer not found locally or in system. Using FetchContent...")
        FetchContent_Declare(
                SDL2_mixer
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
                GIT_TAG release-2.8.1
        )
        FetchContent_MakeAvailable(SDL2_mixer)
    endif()
endif()

# ------------------------------------------
# SDL2_ttf
# ------------------------------------------
set(SDL2_ttf_FOUND FALSE)
import_local_lib(SDL2_ttf SDL2_ttf SDL2_ttf_FOUND)

if (NOT SDL2_ttf_FOUND)
    find_package(SDL2_ttf QUIET)
    if (SDL2_ttf_FOUND)
        message(STATUS "Using system-installed SDL2_ttf.")
    else()
        message(WARNING "SDL2_ttf not found locally or in system. Using FetchContent...")
        FetchContent_Declare(
                SDL2_ttf
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
                GIT_TAG release-2.24.0
        )
        FetchContent_MakeAvailable(SDL2_ttf)
    endif()
endif()
