# Software3DRender

Software 3D Renderer.

Simulate a GPU 3D magic by hands)
I'm developing this project for learning purposes and better understanding how modern 3D APIs looks like inside.

SWR core is platform independent (C++), but you still need OSX and Xcode installed to compile and run it for now.

## Build & run

Open `Software3DRenderer.xcodeproj` in Xcode and run the `Software3DRenderer` scheme, or from the command line:

```sh
# Build the macOS app
xcodebuild -project Software3DRenderer.xcodeproj -scheme Software3DRenderer build

# Run the XCTest suite
xcodebuild test -project Software3DRenderer.xcodeproj -scheme Software3DRenderer -destination 'platform=macOS'
```

## Project layout

- `Software3DRenderer/SWR/` — platform-independent C++ renderer core (the `SWR` namespace).
  - `Bitmap` — raw RGBA/ABGR pixel buffer.
  - `RenderContext` — `Bitmap` + scan buffer used for triangle rasterization (`DrawScanBuffer`, `ScanConvertTriangle`, `FillShape`).
  - `Display` — owns the frame buffer and the active `Scene`; entry point for each frame via `DoDrawFrame(deltaTime)`.
  - `DisplayFactory` — single place where the active scene is selected (swap by editing the `SetScene(...)` lines).
  - `Scene` + `Scenes/` — per-frame `UpdateAndDraw` hook. Bundled scenes: `Star3DFieldScene`, `FillShapeScene`, `TrianglesScene`.
- `Software3DRenderer/` (root) — Cocoa shell. `CanvasView.mm` holds the `SWR::Display` and blits its RGBA buffer to the view; `ViewController.m` drives frames with `CVDisplayLink`.
- `Software3DRendererTests/` — XCTest bundle (Objective-C++) covering `Bitmap` and `RenderContext`.

## Switching scenes

Edit `Software3DRenderer/SWR/DisplayFactory.cpp` and uncomment the `SetScene(...)` line for the scene you want to run.

Have fun!
