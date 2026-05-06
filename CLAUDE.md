# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

Software3DRender is a learning project that simulates a GPU 3D pipeline by hand on the CPU. The renderer core (`SWR` namespace) is plain C++ and platform-independent, but the surrounding app shell, build system, and tests are macOS / Cocoa / Xcode only — there is no CMake or Make-based build.

## Build, run, test

There is no command-line build outside of Xcode. Use either the Xcode IDE or `xcodebuild`:

```sh
# Build the macOS app
xcodebuild -project Software3DRenderer.xcodeproj -scheme Software3DRenderer build

# Run the XCTest suite (Bitmap + RenderContext tests)
xcodebuild test -project Software3DRenderer.xcodeproj -scheme Software3DRenderer -destination 'platform=macOS'

# Run a single test method
xcodebuild test -project Software3DRenderer.xcodeproj -scheme Software3DRenderer \
  -destination 'platform=macOS' \
  -only-testing:Software3DRendererTests/Software3DRendererTests/testRenderContext
```

The two Xcode targets are `Software3DRenderer` (the Cocoa app) and `Software3DRendererTests` (XCTest bundle in `Software3DRendererTests/Software3DRendererTests.mm`). Tests are written in Objective-C++ so they can `#include` the C++ SWR headers directly.

## Architecture

The pipeline is layered as **Bitmap → RenderContext → Display → Scene**, wired together by a factory and driven by a Cocoa view.

- **`SWR::Bitmap`** (`SWR/Bitmap.{h,cpp}`) — owns a raw `unsigned char*` pixel buffer and knows how to clear / write a single pixel. `BitmapColorSpace` selects between `BITMAP_RGBA` and `BITMAP_ABGR` byte ordering. `DrawPixel`'s parameter order is always `(a, b, g, r)` regardless of color space; the color space only affects how those bytes are stored.
- **`SWR::RenderContext`** (`SWR/RenderContext.{h,cpp}`) — extends `Bitmap` and adds a *scan buffer* (two ints per scan-line: xMin, xMax) used for shape filling. `ScanConvertTriangle` emits scan-line spans for a triangle (the caller must pre-sort vertices by Y and pass a handedness), and `FillShape(yMin, yMax)` then rasterizes those spans into the bitmap.
- **`SWR::Display`** (`SWR/Display.{h,cpp}`) — owns one `RenderContext` (the frame buffer) and the currently active `Scene`. `DoDrawFrame(deltaTime)` delegates to the scene; if no scene is set it falls back to a hard-coded scan-buffer demo. `Resize` re-allocates the underlying `RenderContext`.
- **`SWR::Scene`** (`SWR/Scene.{h,cpp}`) — virtual `UpdateAndDraw(deltaTime, renderTarget)` is the per-frame hook. Concrete scenes live in `SWR/Scenes/`:
  - `Star3DFieldScene` — perspective-projected starfield with speed/spread/acceleration parameters.
  - `FillShapeScene` — exercises `DrawScanBuffer` + `FillShape`.
  - `TrianglesScene` — exercises `ScanConvertTriangle` + `FillShape`.
- **`SWR::DisplayFactory`** (`SWR/DisplayFactory.{h,cpp}`) — the single place where the active scene is chosen. To swap scenes, edit the commented `SetScene(...)` lines in `DisplayFactory::GetConfiguredDisplay`; do not add scene-selection logic to `Display` or the Cocoa layer.

Cocoa shell (Objective-C / Objective-C++):

- `CanvasView.mm` is `.mm` so it can hold a `std::shared_ptr<SWR::Display>`. Each `drawRect:` calls `_display->DoDrawFrame`, then blits the raw RGBA buffer to the view via `NSDrawBitmap`. Frame size changes trigger `Display::Resize`.
- `ViewController.m` drives frames with `CVDisplayLink`, computing `deltaTime` from the timestamps and pushing it to `CanvasView` before requesting a redraw.

## Conventions

- **C++ files use `.cpp`/`.h` and live under `Software3DRenderer/SWR/`.** Anything that bridges to Cocoa is Objective-C++ (`.mm`). When you add a file that consumes SWR headers from Objective-C code, the `.m` must become `.mm`.
- **All renderer types live in `namespace SWR`.** Scene subclasses currently live at the global namespace and inherit from `SWR::Scene` — follow that pattern for new scenes in `SWR/Scenes/`.
- **Lifetime is `std::shared_ptr` end-to-end** for `Display`, `RenderContext`, and `Scene`; preserve that — `CanvasView` and `Display` both store shared pointers.
- **New files must be added to the Xcode project** (`Software3DRenderer.xcodeproj/project.pbxproj`) — there is no glob-based build, so a file dropped into `SWR/` will not compile until it is registered with the appropriate target.
