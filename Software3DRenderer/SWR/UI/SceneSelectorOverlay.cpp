#include "SceneSelectorOverlay.h"

#include "PixelFont.h"

namespace SWR {
namespace UI {

namespace {

constexpr int kScale       = 2;
constexpr int kButtonPad   = 6;                 // padding around the arrow glyph
constexpr int kSlotGap     = 8;                 // gap between buttons and label
constexpr int kTopMargin   = 8;
constexpr int kGlyphW      = kFontGlyphW * kScale;
constexpr int kGlyphH      = kFontGlyphH * kScale;
constexpr int kButtonW     = kGlyphW + kButtonPad * 2;
constexpr int kButtonH     = kGlyphH + kButtonPad * 2;

}  // namespace

SceneSelectorOverlay::SceneSelectorOverlay()
    : _left{0,0,0,0}, _right{0,0,0,0}, _label{0,0,0,0}
{
}

void SceneSelectorOverlay::Layout(int bitmapW, int bitmapH,
                                  const char* sceneName,
                                  Rect& left, Rect& right, Rect& label)
{
    int nameW = MeasureString(sceneName ? sceneName : "", kScale);
    int totalW = kButtonW + kSlotGap + nameW + kSlotGap + kButtonW;
    int barX = (bitmapW - totalW) / 2;
    if (barX < 0) barX = 0;
    int barY = kTopMargin;
    if (barY + kButtonH > bitmapH)
        barY = (bitmapH > kButtonH) ? (bitmapH - kButtonH) : 0;

    left  = { barX, barY, kButtonW, kButtonH };
    int labelX = barX + kButtonW + kSlotGap;
    label = { labelX, barY + (kButtonH - kGlyphH) / 2, nameW, kGlyphH };
    int rightX = labelX + nameW + kSlotGap;
    right = { rightX, barY, kButtonW, kButtonH };
}

void SceneSelectorOverlay::Draw(RenderContext& rc, const char* sceneName)
{
    Layout(rc.GetWidth(), rc.GetHeight(), sceneName, _left, _right, _label);

    auto drawButton = [&](const Rect& rct, const char* glyph) {
        rc.FillRect(rct.x, rct.y, rct.w, rct.h, 40, 40, 40, 255);
        // 1-pixel border
        rc.FillRect(rct.x, rct.y, rct.w, 1, 200, 200, 200, 255);
        rc.FillRect(rct.x, rct.y + rct.h - 1, rct.w, 1, 200, 200, 200, 255);
        rc.FillRect(rct.x, rct.y, 1, rct.h, 200, 200, 200, 255);
        rc.FillRect(rct.x + rct.w - 1, rct.y, 1, rct.h, 200, 200, 200, 255);

        int gx = rct.x + (rct.w - kGlyphW) / 2;
        int gy = rct.y + (rct.h - kGlyphH) / 2;
        DrawString(rc, gx, gy, glyph, 230, 230, 230, kScale);
    };

    drawButton(_left,  "<");
    drawButton(_right, ">");

    if (sceneName && *sceneName) {
        DrawString(rc, _label.x, _label.y, sceneName, 240, 240, 240, kScale);
    }
}

int SceneSelectorOverlay::HitTest(int x, int y) const
{
    auto inside = [&](const Rect& r) {
        return r.w > 0 && r.h > 0
            && x >= r.x && x < r.x + r.w
            && y >= r.y && y < r.y + r.h;
    };
    if (inside(_left))  return -1;
    if (inside(_right)) return +1;
    return 0;
}

int SceneSelectorOverlay::HitTestFor(int bitmapW, int bitmapH,
                                     const char* sceneName, int x, int y)
{
    Rect l, r, lbl;
    Layout(bitmapW, bitmapH, sceneName, l, r, lbl);
    SceneSelectorOverlay tmp;
    tmp._left = l;
    tmp._right = r;
    tmp._label = lbl;
    return tmp.HitTest(x, y);
}

}
}
