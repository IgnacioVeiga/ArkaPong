#!/usr/bin/env bash
set -euo pipefail

# Build script for Frontend. If Core was copied locally into core_local it will be used.
# Usage: ./build.sh [path_to_core_root]

CORE_ARG="${1-}"
mkdir -p build
cd build

detect_host_platform() {
  case "$(uname -s)" in
    Linux*) echo "linux" ;;
    Darwin*) echo "macos" ;;
    MINGW*|MSYS*|CYGWIN*) echo "windows" ;;
    *) echo "unknown" ;;
  esac
}

build_core_candidates() {
  local platform="$1"
  local build_root="$2"
  local lib_root="$3"
  local bin_root="$4"

  # Keep shell scripts platform-aware: Linux/macOS should not depend on DLL paths,
  # but Git Bash or MSYS on Windows still benefits from them.
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

HOST_PLATFORM="$(detect_host_platform)"
if [ -n "$CORE_ARG" ]; then
  CORE_ROOT=$(realpath "$CORE_ARG")
  CORE_INC="${CORE_ROOT}/include"
  CORE_BUILD="${CORE_ROOT}/build"
  CORE_LIB=""
  CORE_LIB_CANDIDATES=()
  while IFS= read -r candidate; do
    CORE_LIB_CANDIDATES+=("$candidate")
  done < <(build_core_candidates "$HOST_PLATFORM" "$CORE_BUILD" "${CORE_BUILD}/lib" "${CORE_BUILD}/bin")
  for candidate in "${CORE_LIB_CANDIDATES[@]}"; do
    if [ -f "$candidate" ]; then
      CORE_LIB="$candidate"
      break
    fi
  done
elif [ -d ../core_local ]; then
  CORE_INC=$(realpath ../core_local/include)
  CORE_LIB=""
  CORE_LIB_CANDIDATES=()
  while IFS= read -r candidate; do
    CORE_LIB_CANDIDATES+=("$candidate")
  done < <(build_core_candidates "$HOST_PLATFORM" "../core_local" "../core_local/lib" "../core_local/bin")
  for candidate in "${CORE_LIB_CANDIDATES[@]}"; do
    if [ -f "$candidate" ]; then
      CORE_LIB=$(realpath "$candidate")
      break
    fi
  done
fi

CMAKE_OPTS=(..)
if [ -n "${CORE_INC-}" ]; then
  CMAKE_OPTS+=("-DCORE_INCLUDE_DIR=${CORE_INC}")
fi
if [ -n "${CORE_LIB-}" ]; then
  CMAKE_OPTS+=("-DCORE_LIBRARY=${CORE_LIB}")
fi

cmake "${CMAKE_OPTS[@]}"
cmake --build . -- -j$(nproc || echo 1)

echo "Frontend built in $(pwd)"
