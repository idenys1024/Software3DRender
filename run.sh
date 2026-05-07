#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

BUILD_DIR="build"
BUILD_TYPE="${BUILD_TYPE:-Release}"

if [[ ! -f "$BUILD_DIR/build.ninja" && ! -f "$BUILD_DIR/Makefile" && ! -f "$BUILD_DIR/CMakeCache.txt" ]]; then
    if command -v ninja >/dev/null 2>&1; then
        cmake -S . -B "$BUILD_DIR" -G Ninja -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
    else
        cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
    fi
fi

cmake --build "$BUILD_DIR" --config "$BUILD_TYPE"

case "$(uname -s)" in
    Darwin) exec "$BUILD_DIR/Software3DRenderer.app/Contents/MacOS/Software3DRenderer" "$@" ;;
    MINGW*|MSYS*|CYGWIN*) exec "$BUILD_DIR/$BUILD_TYPE/Software3DRenderer.exe" "$@" ;;
    *) exec "$BUILD_DIR/Software3DRenderer" "$@" ;;
esac
