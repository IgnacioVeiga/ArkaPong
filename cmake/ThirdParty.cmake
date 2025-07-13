find_package(SDL2 QUIET)
find_package(SDL2_mixer QUIET)
find_package(SDL2_ttf QUIET)

if(NOT SDL2_FOUND OR NOT SDL2_mixer_FOUND OR NOT SDL2_ttf_FOUND)
    message(STATUS "Downloading SDL2...")

    FetchContent_Declare(SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.32.8
    )

    FetchContent_Declare(SDL2_mixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
            GIT_TAG release-2.8.1
    )

    FetchContent_Declare(SDL2_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-2.24.0
    )

    FetchContent_MakeAvailable(SDL2 SDL2_mixer SDL2_ttf)
endif()
