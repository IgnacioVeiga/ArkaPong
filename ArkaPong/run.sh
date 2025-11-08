#!/usr/bin/env bash
set -euo pipefail

# Run ArkaPong: look in build/bin/ first, then fallback to build/
TARGET=ArkaPong
POSSIBLE=( 
  "build/bin/$TARGET/$TARGET" 
  "build/bin/$TARGET/$TARGET.exe"
  "build/bin/$TARGET" 
  "build/bin/$TARGET.exe" 
  "build/$TARGET" 
)
for p in "${POSSIBLE[@]}"; do
  if [ -f "$p" ]; then
    cd "$(dirname "$p")"
    exec "./$(basename "$p")"
  fi
done

echo "Executable not found in build/bin or build/. Please build first using ./build.sh"
exit 1
