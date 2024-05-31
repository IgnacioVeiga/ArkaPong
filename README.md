# ArkaPong (pre-alpha)

ArkaPong is a hybrid game combining the classic "Arkanoid" (from NES) with "Pong". This game is being developed from scratch in C++ using SDL2 libraries. It is currently in pre-alpha stage and requires structural improvements. The game is intended to be compatible with Windows and any Linux distributions. Use CMake for the build process.

## Features (planned)
- Classic Arkanoid and Pong gameplay elements
- Single-player and multiplayer modes
- Power-ups and special abilities
- Multiple levels and game modes

### Arkanoid
![Arkanoid](https://images.squarespace-cdn.com/content/v1/5e004a01af59914152deea6d/1604237320287-Q5RPEEJ8B77OTM4OSGXV/Brick+Breaker.gif)

### PONG
![PONG](https://www.retrogames.cz/games/530/Pong-gameplay.gif)

### ArkaPong
![pre-alpha_ArkaPong_gameplay](https://github.com/IgnacioVeiga/ArkaPong/assets/42973262/5912f11a-54bc-495f-80a5-e85f92a2490c)

### Prerequisites
- [Git](https://git-scm.com/) (optional)
- [CMake](https://cmake.org/download/) (version 3.29+)
- A compiler compatible with C++ 17.
  - For Windows: MinGW-w64, MSVC, etc.
  - For Linux: GCC, Clang, etc.
- Libraries:
  - [SDL2](https://github.com/libsdl-org/SDL) (2.30.3)
  - [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer) (2.8.0)
  - [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf) (2.22.0)

### Build
1. Download source code or clone the repository with Git
    ```sh
    git clone https://github.com/IgnacioVeiga/ArkaPong.git
    cd ArkaPong
    ```
    
2. Build the project using CMake (check the CMakeLists.txt file)
    ``` sh
    cmake -B build
    cmake --build build
    ```

3. Check that the executable should be accompanied by the “assets” folder in order to run. Finally, to run the game check build folder that can look like this:
    - Linux
    ``` sh
    /build/bin/ArkaPong
    ```
    - Windows
    ``` cmd
    /build/bin/ArkaPong.exe
    ```

## Additional Notes
- CMake Presets: If you use Visual Studio Code, you can configure CMake Tools to handle presets and simplify the configuration and compilation process.

## Cleaning the project
To remove all files generated by CMake and the build, simply delete the build directory.

## Contributing
Any contributions are welcome! Please fork the repository and create a pull request with your changes.
