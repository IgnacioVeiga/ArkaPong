#!/usr/bin/env bash
set -euo pipefail

if [ -z "${1-}" ]; then
  echo "Usage: $0 /path/to/Core/root"
  exit 1
fi
CORE_ROOT=$(realpath "$1")
SRC_INC="$CORE_ROOT/include"
SRC_BUILD="$CORE_ROOT/build"
DEST_DIR="$(pwd)/core_local"

if [ ! -d "$SRC_INC" ]; then
  echo "Missing $SRC_INC"
  exit 1
fi

mkdir -p "$DEST_DIR/include" "$DEST_DIR/lib"
cp -r "$SRC_INC/"* "$DEST_DIR/include/"

if [ -f "$SRC_BUILD/libCore.so" ]; then
  cp "$SRC_BUILD/libCore.so" "$DEST_DIR/lib/"
elif [ -f "$SRC_BUILD/Core.dll" ]; then
  cp "$SRC_BUILD/Core.dll" "$DEST_DIR/lib/"
elif ls "$SRC_BUILD"/libCore.* 1> /dev/null 2>&1; then
  cp "$SRC_BUILD"/libCore.* "$DEST_DIR/lib/" || true
else
  echo "No binaries found in $SRC_BUILD. Ensure Core was built first."
fi

echo "Core copied to $DEST_DIR (headers -> include, library -> lib)"