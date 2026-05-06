# Software3DRender

Software 3D Renderer.

Simulate a GPU 3D magic by hands)
I'm developing this project for learning purposes and better understanding how modern 3D APIs looks like inside.

The SWR core is platform-independent C++. The application shell is built on
SDL3 and CMake. Builds are verified on Windows, Linux, and macOS.

## Build & run

Requirements: CMake ≥ 3.21, a C++14 toolchain, git. SDL3 and Catch2 are
pulled in automatically by CMake's `FetchContent` on first configure.

### Linux

On Debian/Ubuntu, install the X11 development headers SDL3 builds against
(or the equivalent on your distro):

```sh
sudo apt install build-essential cmake ninja-build \
                 libx11-dev libxext-dev
```

Then:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/Software3DRenderer
ctest --test-dir build --output-on-failure
```

### Windows

```sh
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
build\Release\Software3DRenderer.exe
ctest --test-dir build -C Release --output-on-failure
```

### macOS

Requires Xcode Command Line Tools (`xcode-select --install`).

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/Software3DRenderer.app/Contents/MacOS/Software3DRenderer
ctest --test-dir build --output-on-failure
```

The shell is built as a `MACOSX_BUNDLE`, so the binary lives inside the
`.app`. CMake pins `CMAKE_OSX_DEPLOYMENT_TARGET` to `10.15` if you do
not override it; pass `-DCMAKE_OSX_DEPLOYMENT_TARGET=...` to change it,
or `-DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"` for a universal binary.

## Project layout

- `Software3DRenderer/SWR/` — platform-independent C++ renderer core
  (`SWR` namespace).
  - `Bitmap` — raw RGBA/ABGR pixel buffer.
  - `RenderContext` — `Bitmap` + scan buffer used for triangle rasterization
    (`DrawScanBuffer`, `ScanConvertTriangle`, `FillShape`).
  - `Display` — owns the frame buffer and the active `Scene`; entry point
    for each frame via `DoDrawFrame(deltaTime)`.
  - `DisplayFactory` — single place where the active scene is selected
    (swap by editing the `SetScene(...)` lines).
  - `Scene` + `Scenes/` — per-frame `UpdateAndDraw` hook. Bundled scenes:
    `Star3DFieldScene`, `FillShapeScene`, `TrianglesScene`.
- `app/main.cpp` — SDL3 platform shell: opens a resizable window, drives
  the frame loop, blits the RGBA buffer via a streaming `SDL_Texture`.
- `tests/swr_tests.cpp` — Catch2 tests for `Bitmap` and `RenderContext`.

## Switching scenes

Edit `Software3DRenderer/SWR/DisplayFactory.cpp` and uncomment the
`SetScene(...)` line for the scene you want to run.

Have fun!
