# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

Software3DRender is a learning project that simulates a GPU 3D pipeline by hand on the CPU. The renderer core (`SWR` namespace) is plain C++ and platform-independent. The application shell is SDL3 + CMake; builds are verified on Windows and Linux.

## Build, run, test

Requirements: CMake ≥ 3.21, a C++14 toolchain, git. SDL3 and Catch2 are vendored via `FetchContent` and downloaded on first configure. On Linux SDL3 needs X11 dev headers (`libx11-dev libxext-dev` on Debian/Ubuntu).

```sh
# Linux (Ninja)
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/Software3DRenderer
ctest --test-dir build --output-on-failure

# Windows (Visual Studio)
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
build\Release\Software3DRenderer.exe
ctest --test-dir build -C Release --output-on-failure

# Run a single Catch2 test by name (Linux)
./build/swr_tests "RenderContext FillShape rasterizes inside scan-buffer rows"

# Or by tag
./build/swr_tests "[Bitmap]"
```

Note: do **not** define `SDL_MAIN_USE_CALLBACKS` (even as `0`) in `app/main.cpp` — SDL checks `#ifdef`, not the value, so any definition opts in to callback mode and produces a duplicate `SDL_main` link error. Just `#include <SDL3/SDL_main.h>` and write a normal `int main`.

The CMake project produces three artifacts: the `swr` static library (the renderer core), the `Software3DRenderer` executable (SDL3 shell), and `swr_tests` (Catch2 binary registered with CTest).

## Architecture

The pipeline is layered as **Bitmap → RenderContext → Display → Scene**, wired together by a factory and driven by an SDL3 main loop.

- **`SWR::Bitmap`** (`SWR/Bitmap.{h,cpp}`) — owns a raw `unsigned char*` pixel buffer and knows how to clear / write a single pixel. `BitmapColorSpace` selects between `BITMAP_RGBA` and `BITMAP_ABGR` byte ordering. `DrawPixel`'s parameter order is always `(a, b, g, r)` regardless of color space; the color space only affects how those bytes are stored. The default `BITMAP_RGBA` layout matches `SDL_PIXELFORMAT_RGBA32` byte-for-byte, so `SDL_UpdateTexture` consumes `Display::GetDisplayRGBAData()` directly with no conversion.
- **`SWR::RenderContext`** (`SWR/RenderContext.{h,cpp}`) — extends `Bitmap` and adds a *scan buffer* (two ints per scan-line: xMin, xMax) used for shape filling. `ScanConvertTriangle` emits scan-line spans for a triangle (the caller must pre-sort vertices by Y and pass a handedness), and `FillShape(yMin, yMax)` then rasterizes those spans into the bitmap.
- **`SWR::Display`** (`SWR/Display.{h,cpp}`) — owns one `RenderContext` (the frame buffer) and the currently active `Scene`. `DoDrawFrame(deltaTime)` delegates to the scene; if no scene is set it falls back to a hard-coded scan-buffer demo. `Resize` re-allocates the underlying `RenderContext`.
- **`SWR::Scene`** (`SWR/Scene.{h,cpp}`) — virtual `UpdateAndDraw(deltaTime, renderTarget)` is the per-frame hook. Concrete scenes live in `SWR/Scenes/`:
  - `Star3DFieldScene` — perspective-projected starfield with speed/spread/acceleration parameters.
  - `FillShapeScene` — exercises `DrawScanBuffer` + `FillShape`.
  - `TrianglesScene` — exercises `ScanConvertTriangle` + `FillShape`.
- **`SWR::DisplayFactory`** (`SWR/DisplayFactory.{h,cpp}`) — the single place where the active scene is chosen. To swap scenes, edit the commented `SetScene(...)` lines in `DisplayFactory::GetConfiguredDisplay`; do not add scene-selection logic to `Display` or to the SDL shell.

Platform shell (`app/main.cpp`):

- One `main` that calls `SDL_Init`, creates a resizable `SDL_Window` + `SDL_Renderer` + a streaming `SDL_Texture` (`SDL_PIXELFORMAT_RGBA32`). Includes `<SDL3/SDL_main.h>` for the platform entry-point shim — see the build note above about not defining `SDL_MAIN_USE_CALLBACKS`.
- Builds the renderer via `SWR::DisplayFactory::GetConfiguredDisplay` and stores it in a `std::shared_ptr<SWR::Display>`.
- Each iteration: pump SDL events, compute `deltaTime` from `SDL_GetTicks`, call `Display::DoDrawFrame`, push the bitmap into the texture with `SDL_UpdateTexture`, then `SDL_RenderTexture` + `SDL_RenderPresent`.
- On `SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED` it calls `Display::Resize` and recreates the texture; on `SDL_EVENT_QUIT` it tears everything down in reverse.

## Conventions

- **C++ files use `.cpp`/`.h` and live under `Software3DRenderer/SWR/`.** All renderer types live in `namespace SWR`. Scene subclasses currently live at the global namespace and inherit from `SWR::Scene` — follow that pattern for new scenes in `SWR/Scenes/`.
- **Lifetime is `std::shared_ptr` end-to-end** for `Display`, `RenderContext`, and `Scene`; preserve that — the SDL shell and `Display` both store shared pointers.
- **New SWR source files must be added to the `swr` target** in the root `CMakeLists.txt` — sources are listed explicitly, there is no glob, so a `.cpp` dropped into `SWR/` will not compile until it is registered.
- **Tests use Catch2 v3** (`tests/swr_tests.cpp`); add new cases via `TEST_CASE` and assert with `REQUIRE`. Tag cases with the class under test (e.g. `[Bitmap]`, `[RenderContext]`) so they can be filtered on the command line.
