# ArkaPong (pre-alpha)

ArkaPong is a hybrid game combining the classic "Arkanoid" (from NES) with "Pong". This game is being developed from scratch in C++ using SDL2 libraries. It is currently in pre-alpha stage and requires structural improvements. It should be compatible with Windows and any Linux distribution.

## Features (planned)
- Classic Arkanoid and Pong gameplay elements
- Single-player and multiplayer
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
- [CMake](https://cmake.org/download/) (not required for Windows)
- Libraries:
  - [SDL2](https://github.com/libsdl-org/SDL) (2.30.1)
  - [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer) (2.8.0)
  - [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf) (2.22.0)
- A compiler for C++ 17.
  - Windows: MSVC v143-VS 2022
  - Linux: GCC, Clang or any compatible with ``CMakeLists.txt``.
- On Windows you can use VCPKG to download SDL2 packages.

### Build
1. Download source code or clone the repository with Git
   ```sh
   git clone https://github.com/IgnacioVeiga/ArkaPong.git
   cd ArkaPong
   ```
2. - Linux: Use CMake (check the ``CMakeLists.txt`` file) and run:
   ``` sh
   cmake -B build
   cmake --build build
   ```
    - Windows: Use Microsoft Visual Studio 2022 to build and run.

3. Finally check the build folder, the executable should be accompanied by the “assets” folder in order to run.

## Additional Notes
If you use Visual Studio Code, you can configure CMake Tools to handle presets and simplify the configuration and compilation process.

## Cleaning the project
To remove all files generated by CMake build, simply delete the build directory. Microsoft Visual Studio 2022 already has a clean function.

## Contributing
I'm very new to C/C++, so any contributions are welcome. Please fork the repository and create a pull request with your changes.

## "ECS" version
I'm working on implementing the Entity Component System design pattern, for this I'm basing my work on this post by Austin Morlan:
https://austinmorlan.com/posts/entity_component_system/
