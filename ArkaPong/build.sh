#!/usr/bin/env bash
set -euo pipefail

# Build script for ArkaPong. If Core was copied locally into core_local it will be used.
# Usage: ./build.sh [path_to_core_root]

CORE_ARG="${1-}"
mkdir -p build
cd build
if [ -n "$CORE_ARG" ]; then
  CORE_ROOT=$(realpath "$CORE_ARG")
  CORE_INC="${CORE_ROOT}/include"
  # heuristic: look for the library under Core's build/ directory
  if [ -f "${CORE_ROOT}/build/libCore.so" ]; then
    CORE_LIB="${CORE_ROOT}/build/libCore.so"
  elif [ -f "${CORE_ROOT}/build/Core.dll" ]; then
    CORE_LIB="${CORE_ROOT}/build/Core.dll"
  elif [ -f "${CORE_ROOT}/build/libCore.a" ]; then
    CORE_LIB="${CORE_ROOT}/build/libCore.a"
  else
    CORE_LIB=""
  fi
elif [ -d ../core_local ]; then
  CORE_INC=$(realpath ../core_local/include)
  CORE_LIB=$(realpath ../core_local/lib/* 2>/dev/null || true)
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

echo "ArkaPong built in $(pwd)"