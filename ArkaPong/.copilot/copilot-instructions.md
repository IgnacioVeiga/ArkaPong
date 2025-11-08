```instructions
# ArkaPong - LLM Instructions

Summary:
- ArkaPong is the game executable. It depends on the portable Core library and SDL2.
- The project contains scripts to copy a built Core from a local source tree into `core_local/`.

Guidance for LLMs:
- When editing build scripts, keep Core as a portable library (do not add system installs).
- Use the local `cmake/ThirdParty.cmake` to fetch or use SDL2.
- Prefer small, safe changes: docs, scripts, and minor CMake fixes. Avoid cross-repo assumptions.

```