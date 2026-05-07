#ifndef __Software3DRenderer__PixelFont__
#define __Software3DRenderer__PixelFont__

#include "RenderContext.h"

namespace SWR {
namespace UI {

constexpr int kFontGlyphW = 5;
constexpr int kFontGlyphH = 7;
constexpr int kFontAdvance = kFontGlyphW + 1;

int MeasureString(const char* text, int scale);

void DrawString(RenderContext& rc,
                int x, int y,
                const char* text,
                uchar r, uchar g, uchar b,
                int scale);

}
}

#endif
