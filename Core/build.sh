#!/usr/bin/env bash
set -euo pipefail

# Build script for the portable Core library
# Usage: ./build.sh

mkdir -p build
cd build
cmake ..
cmake --build . -- -j$(nproc || echo 1)

echo "Core built in $(pwd)"