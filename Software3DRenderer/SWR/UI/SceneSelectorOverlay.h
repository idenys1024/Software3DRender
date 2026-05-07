#ifndef __Software3DRenderer__SceneSelectorOverlay__
#define __Software3DRenderer__SceneSelectorOverlay__

#include "RenderContext.h"

namespace SWR {
namespace UI {

class SceneSelectorOverlay
{
public:
    struct Rect { int x, y, w, h; };

    SceneSelectorOverlay();

    // Lays out and draws the < SCENE_NAME > bar at the top-center of `rc`.
    // Caches the rects so HitTest can be called immediately afterward.
    void Draw(RenderContext& rc, const char* sceneName);

    // Returns -1 if (x, y) hit the previous-scene button, +1 if next, 0 otherwise.
    // Uses the rects computed by the most recent Draw call (or zero-rects pre-Draw).
    int HitTest(int x, int y) const;

    // Same as HitTest but computes rects from explicit dimensions instead of
    // requiring a prior Draw — handy for unit tests.
    static int HitTestFor(int bitmapW, int bitmapH, const char* sceneName,
                          int x, int y);

    // Layout introspection (after Draw).
    Rect LeftButton()  const { return _left; }
    Rect RightButton() const { return _right; }
    Rect Label()       const { return _label; }

private:
    static void Layout(int bitmapW, int bitmapH, const char* sceneName,
                       Rect& left, Rect& right, Rect& label);

    Rect _left;
    Rect _right;
    Rect _label;
};

}
}

#endif
