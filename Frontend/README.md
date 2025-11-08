Frontend - GUI / Tooling Project

Overview

Frontend is a helper GUI project that uses the Core library. It contains ImGui sources and depends on SDL2.

Quick start

If you have Core source locally:

```bash
./copy_core.sh /path/to/Core
./build.sh
./run.sh
```

If you have only a prebuilt Core library, place headers and library under `core_local/` as in ArkaPong.

Notes

- Build scripts for Windows (cmd/.bat) and PowerShell (.ps1) are provided.
- SDL2 is fetched/managed via `cmake/ThirdParty.cmake` in this folder.
