Core - Portable Game Engine (C++)

Overview

Core is a portable C++17 library containing game engine code (ECS, managers, utils) used by ArkaPong and Frontend. This folder is intended to be a standalone project: build it, and then copy the headers and built library into downstream projects.

Quick build

Unix/macOS:
```bash
./build.sh
```

Windows (cmd):
```
build.bat
```

Windows (PowerShell):
```
./build.ps1
```

Using the library from another project

1. Build Core.
2. Copy headers (Core/include) and the built library from Core/build into the consumer project. You can use the consumer project's `copy_core` script, or copy manually.

Notes

- This project contains a `cmake/ThirdParty.cmake` helper that fetches or uses local SDL2 builds. The project is self-contained for dependency retrieval.
- Core is portable: it is not installed into the system. Consumers should point their CMake via `-DCORE_INCLUDE_DIR=/path/to/include -DCORE_LIBRARY=/path/to/libCore.so` or use the provided copy script.
