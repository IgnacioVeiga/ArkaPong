# ==========================================
# ThirdParty.cmake — SDL2 management logic
# ==========================================

include(FetchContent)

# 1. Try to use a system installation
find_package(SDL2 QUIET)
find_package(SDL2_mixer QUIET)
find_package(SDL2_ttf QUIET)

if (SDL2_FOUND AND SDL2_mixer_FOUND AND SDL2_ttf_FOUND)
    message(STATUS "Using system-installed SDL2 libraries.")

else()
    message(WARNING "System SDL2 not found. Looking for local precompiled version...")

    # 2. Search in local folder "ThirdParty/SDL2"
    set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/ThirdParty")

    set(SDL2_LOCAL_DIR "${THIRDPARTY_DIR}/SDL2")
    set(SDL2_MIXER_LOCAL_DIR "${THIRDPARTY_DIR}/SDL2_mixer")
    set(SDL2_TTF_LOCAL_DIR "${THIRDPARTY_DIR}/SDL2_ttf")

    if (EXISTS "${SDL2_LOCAL_DIR}/include" AND EXISTS "${SDL2_LOCAL_DIR}/lib")
        message(STATUS "Using local SDL2 from ${SDL2_LOCAL_DIR}")

        add_library(SDL2::SDL2 SHARED IMPORTED)
        set_target_properties(SDL2::SDL2 PROPERTIES
                IMPORTED_LOCATION "${SDL2_LOCAL_DIR}/lib/SDL2.dll"
                IMPORTED_IMPLIB "${SDL2_LOCAL_DIR}/lib/SDL2.lib"
                INTERFACE_INCLUDE_DIRECTORIES "${SDL2_LOCAL_DIR}/include"
        )

        add_library(SDL2::SDL2main SHARED IMPORTED)
        set_target_properties(SDL2::SDL2main PROPERTIES
                IMPORTED_LOCATION "${SDL2_LOCAL_DIR}/lib/SDL2main.dll"
                IMPORTED_IMPLIB "${SDL2_LOCAL_DIR}/lib/SDL2main.lib"
                INTERFACE_INCLUDE_DIRECTORIES "${SDL2_LOCAL_DIR}/include"
        )

        # Example for SDL_mixer and SDL_ttf
        add_library(SDL2_mixer SHARED IMPORTED)
        set_target_properties(SDL2_mixer PROPERTIES
                IMPORTED_LOCATION "${SDL2_MIXER_LOCAL_DIR}/lib/SDL2_mixer.dll"
                IMPORTED_IMPLIB "${SDL2_MIXER_LOCAL_DIR}/lib/SDL2_mixer.lib"
                INTERFACE_INCLUDE_DIRECTORIES "${SDL2_MIXER_LOCAL_DIR}/include"
        )

        add_library(SDL2_ttf SHARED IMPORTED)
        set_target_properties(SDL2_ttf PROPERTIES
                IMPORTED_LOCATION "${SDL2_TTF_LOCAL_DIR}/lib/SDL2_ttf.dll"
                IMPORTED_IMPLIB "${SDL2_TTF_LOCAL_DIR}/lib/SDL2_ttf.lib"
                INTERFACE_INCLUDE_DIRECTORIES "${SDL2_TTF_LOCAL_DIR}/include"
        )

    else()
        message(WARNING "Local SDL2 not found. Falling back to FetchContent...")

        # 3. If neither system nor local is found, use FetchContent
        FetchContent_Declare(
                SDL2
                GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
                GIT_TAG release-2.32.8
        )
        FetchContent_Declare(
                SDL2_mixer
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
                GIT_TAG release-2.8.1
        )
        FetchContent_Declare(
                SDL2_ttf
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
                GIT_TAG release-2.24.0
        )

        FetchContent_MakeAvailable(SDL2 SDL2_mixer SDL2_ttf)
    endif()
endif()
