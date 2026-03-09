#!/usr/bin/env bash
set -euo pipefail

if [ -z "${1-}" ]; then
  echo "Usage: $0 /path/to/Core/root"
  exit 1
fi
CORE_ROOT=$(realpath "$1")
SRC_INC="$CORE_ROOT/include"
SRC_BUILD="$CORE_ROOT/build"
SRC_LIB="$SRC_BUILD/lib"
SRC_BIN="$SRC_BUILD/bin"
DEST_DIR="$(pwd)/core_local"

detect_host_platform() {
  case "$(uname -s)" in
    Linux*) echo "linux" ;;
    Darwin*) echo "macos" ;;
    MINGW*|MSYS*|CYGWIN*) echo "windows" ;;
    *) echo "unknown" ;;
  esac
}

build_binary_candidates() {
  local platform="$1"
  local build_root="$2"
  local lib_root="$3"
  local bin_root="$4"

  case "$platform" in
    windows)
      printf '%s\n' \
        "${lib_root}/Core.lib" \
        "${lib_root}/libCore.lib" \
        "${bin_root}/Core.dll" \
        "${bin_root}/libCore.dll" \
        "${build_root}/Core.lib" \
        "${build_root}/libCore.lib" \
        "${build_root}/Core.dll"
      ;;
    macos)
      printf '%s\n' \
        "${lib_root}/libCore.dylib" \
        "${lib_root}/libCore.a" \
        "${build_root}/libCore.dylib" \
        "${build_root}/libCore.a"
      ;;
    linux|unknown)
      printf '%s\n' \
        "${lib_root}/libCore.so" \
        "${lib_root}/libCore.a" \
        "${build_root}/libCore.so" \
        "${build_root}/libCore.a"
      ;;
  esac
}

if [ ! -d "$SRC_INC" ]; then
  echo "Missing $SRC_INC"
  exit 1
fi

mkdir -p "$DEST_DIR/include" "$DEST_DIR/lib"
cp -r "$SRC_INC/"* "$DEST_DIR/include/"

FOUND_BIN=0
BINARY_CANDIDATES=()
while IFS= read -r candidate; do
  BINARY_CANDIDATES+=("$candidate")
done < <(build_binary_candidates "$(detect_host_platform)" "$SRC_BUILD" "$SRC_LIB" "$SRC_BIN")
for candidate in "${BINARY_CANDIDATES[@]}"; do
  if [ -f "$candidate" ]; then
    cp "$candidate" "$DEST_DIR/lib/"
    FOUND_BIN=1
  fi
done

if [ "$FOUND_BIN" -eq 0 ]; then
  echo "No binaries found in $SRC_BUILD. Ensure Core was built first."
fi

echo "Core copied to $DEST_DIR (headers -> include, library -> lib)"
