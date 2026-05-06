#include <catch2/catch_test_macros.hpp>

#include <random>

#include "Bitmap.h"
#include "Display.h"
#include "DisplayFactory.h"
#include "FillShapeScene.h"
#include "RenderContext.h"
#include "Vertex.h"

using SWR::Bitmap;
using SWR::BITMAP_ABGR;
using SWR::BITMAP_RGBA;
using SWR::Display;
using SWR::DisplayFactory;
using SWR::RenderContext;
using SWR::Vertex;
using SWR::uchar;

namespace {

std::mt19937& Rng()
{
    static std::mt19937 rng(std::random_device{}());
    return rng;
}

int RandInt(int lo, int hi)
{
    std::uniform_int_distribution<int> d(lo, hi);
    return d(Rng());
}

uchar AlphaByteAt(const uchar* data, int x, int y, int w)
{
    return data[(x + y * w) * 4 + 3];
}

}  // namespace

TEST_CASE("RenderContext FillShape rasterizes inside scan-buffer rows",
          "[RenderContext]")
{
    constexpr int kMinW = 20;
    constexpr int kMinH = 20;
    constexpr int kMaxW = 2048;
    constexpr int kMaxH = 2048;

    int w = RandInt(kMinW, kMaxW - 1);
    int h = RandInt(kMinH, kMaxH - 1);

    RenderContext rc(w, h);
    const uchar clearVal = 28;
    const uchar testR    = 255;
    rc.Clear(clearVal);

    for (int j = 5; j < 10; j++)
        rc.DrawScanBuffer(j, 10 - j, 10 + j);
    rc.FillShape(5, 10);

    struct Point { int x; int y; };

    const Point inside[] = { {5, 5}, {14, 5}, {14, 9} };
    for (const auto& p : inside) {
        int index = (p.x + p.y * w) * 4;
        REQUIRE(rc.GetComponentsData()[index + 3] == testR);
    }

    const Point outside[] = { {4, 5}, {15, 5}, {14, 10} };
    for (const auto& p : outside) {
        int index = (p.x + p.y * w) * 4;
        REQUIRE(rc.GetComponentsData()[index + 3] == clearVal);
    }
}

TEST_CASE("Bitmap clear and DrawPixel honor color space",
          "[Bitmap]")
{
    constexpr int kMinW = 10;
    constexpr int kMinH = 10;
    constexpr int kMaxW = 2048;
    constexpr int kMaxH = 2048;

    int w = RandInt(kMinW, kMaxW - 1);
    int h = RandInt(kMinH, kMaxH - 1);

    SECTION("ABGR layout") {
        Bitmap bm(w, h, BITMAP_ABGR);
        uchar clearVal = static_cast<uchar>(RandInt(0, 254));
        bm.Clear(clearVal);
        for (int i = 0; i < w * h * 4; i++)
            REQUIRE(bm.GetComponentsData()[i] == clearVal);

        for (int i = 0; i < 25; i++) {
            uchar a  = static_cast<uchar>(RandInt(0, 254));
            uchar bC = static_cast<uchar>(RandInt(0, 254));
            uchar g  = static_cast<uchar>(RandInt(0, 254));
            uchar r  = static_cast<uchar>(RandInt(0, 254));
            int   px = RandInt(0, w - 1);
            int   py = RandInt(0, h - 1);
            int   index = (px + py * w) * 4;

            bm.DrawPixel(px, py, a, bC, g, r);
            REQUIRE(bm.GetComponentsData()[index + 0] == a);
            REQUIRE(bm.GetComponentsData()[index + 1] == bC);
            REQUIRE(bm.GetComponentsData()[index + 2] == g);
            REQUIRE(bm.GetComponentsData()[index + 3] == r);
        }
    }

    SECTION("RGBA layout") {
        for (int i = 0; i < 25; i++) {
            Bitmap bm(w, h, BITMAP_RGBA);
            uchar a  = static_cast<uchar>(RandInt(0, 254));
            uchar bC = static_cast<uchar>(RandInt(0, 254));
            uchar g  = static_cast<uchar>(RandInt(0, 254));
            uchar r  = static_cast<uchar>(RandInt(0, 254));
            int   px = RandInt(0, w - 1);
            int   py = RandInt(0, h - 1);
            int   index = (px + py * w) * 4;

            bm.DrawPixel(px, py, a, bC, g, r);
            REQUIRE(bm.GetComponentsData()[index + 0] == r);
            REQUIRE(bm.GetComponentsData()[index + 1] == g);
            REQUIRE(bm.GetComponentsData()[index + 2] == bC);
            REQUIRE(bm.GetComponentsData()[index + 3] == a);
        }
    }
}

TEST_CASE("Bitmap DrawPixel rejects out-of-bounds coordinates",
          "[Bitmap]")
{
    constexpr int w = 16;
    constexpr int h = 16;
    const uchar clearVal = 7;

    Bitmap bm(w, h, BITMAP_RGBA);
    bm.Clear(clearVal);

    const struct { int x; int y; } cases[] = {
        {-1,  0}, { 0, -1}, {-1, -1}, {-100, -100},
        { w,  0}, { 0,  h}, { w,  h}, {w + 5, h + 5},
    };
    for (const auto& c : cases) {
        bm.DrawPixel(c.x, c.y, 255, 255, 255, 255);
    }

    for (int i = 0; i < w * h * 4; i++)
        REQUIRE(bm.GetComponentsData()[i] == clearVal);

    SECTION("last in-bounds pixel is writable") {
        bm.DrawPixel(w - 1, h - 1, 1, 2, 3, 4);
        const uchar* data = bm.GetComponentsData();
        int idx = ((w - 1) + (h - 1) * w) * 4;
        REQUIRE(data[idx + 0] == 4);
        REQUIRE(data[idx + 1] == 3);
        REQUIRE(data[idx + 2] == 2);
        REQUIRE(data[idx + 3] == 1);
    }
}

TEST_CASE("Bitmap GetWidth/GetHeight return constructor values",
          "[Bitmap]")
{
    Bitmap bm(37, 91, BITMAP_RGBA);
    REQUIRE(bm.GetWidth() == 37);
    REQUIRE(bm.GetHeight() == 91);
}

TEST_CASE("RenderContext DrawScanBuffer rejects out-of-range rows",
          "[RenderContext]")
{
    constexpr int w = 32;
    constexpr int h = 16;

    RenderContext rc(w, h);
    rc.Clear(0);

    rc.DrawScanBuffer(-1, 0, w);
    rc.DrawScanBuffer(h, 0, w);
    rc.DrawScanBuffer(h + 100, 0, w);

    for (int j = 0; j < h; j++)
        rc.DrawScanBuffer(j, 0, w);
    rc.FillShape(0, h);

    for (int i = 0; i < w * h * 4; i++)
        REQUIRE(rc.GetComponentsData()[i] == 255);
}

TEST_CASE("RenderContext ScanConvertTriangle handedness=0 fills right triangle",
          "[RenderContext]")
{
    constexpr int w = 16;
    constexpr int h = 16;
    RenderContext rc(w, h);
    rc.Clear(0);

    rc.ScanConvertTriangle(Vertex(0, 0), Vertex(10, 0), Vertex(0, 10), 0);
    rc.FillShape(0, 10);

    const uchar* data = rc.GetComponentsData();

    const struct { int x; int y; } inside[] = {
        {0, 0}, {5, 4}, {9, 0}, {0, 9}
    };
    for (const auto& p : inside)
        REQUIRE(AlphaByteAt(data, p.x, p.y, w) == 255);

    const struct { int x; int y; } outside[] = {
        {5, 5}, {1, 9}, {10, 0}
    };
    for (const auto& p : outside)
        REQUIRE(AlphaByteAt(data, p.x, p.y, w) == 0);
}

TEST_CASE("RenderContext ScanConvertTriangle handedness=1 fills mirrored triangle",
          "[RenderContext]")
{
    constexpr int w = 16;
    constexpr int h = 16;
    RenderContext rc(w, h);
    rc.Clear(0);

    rc.ScanConvertTriangle(Vertex(10, 0), Vertex(0, 0), Vertex(0, 10), 1);
    rc.FillShape(0, 10);

    const uchar* data = rc.GetComponentsData();
    REQUIRE(AlphaByteAt(data, 0, 0, w) == 255);
    REQUIRE(AlphaByteAt(data, 9, 0, w) == 255);
    REQUIRE(AlphaByteAt(data, 0, 9, w) == 255);
    REQUIRE(AlphaByteAt(data, 5, 4, w) == 255);

    REQUIRE(AlphaByteAt(data, 10, 0, w) == 0);
    REQUIRE(AlphaByteAt(data, 5, 5, w) == 0);
    REQUIRE(AlphaByteAt(data, 1, 9, w) == 0);
}

TEST_CASE("RenderContext ScanConvertTriangle handles degenerate triangle",
          "[RenderContext]")
{
    constexpr int w = 16;
    constexpr int h = 16;
    RenderContext rc(w, h);
    rc.Clear(0);

    for (int j = 0; j < h; j++)
        rc.DrawScanBuffer(j, 0, 0);

    rc.ScanConvertTriangle(Vertex(0, 5), Vertex(5, 5), Vertex(10, 5), 0);
    rc.FillShape(0, h);

    for (int i = 0; i < w * h * 4; i++)
        REQUIRE(rc.GetComponentsData()[i] == 0);
}

TEST_CASE("Vertex constructors and accessors round-trip",
          "[Vertex]")
{
    Vertex def;
    REQUIRE(def.GetX() == 0.0f);
    REQUIRE(def.GetY() == 0.0f);

    Vertex v(3.5f, -2.25f);
    REQUIRE(v.GetX() == 3.5f);
    REQUIRE(v.GetY() == -2.25f);

    v.SetX(11.0f);
    REQUIRE(v.GetX() == 11.0f);
    REQUIRE(v.GetY() == -2.25f);

    v.SetY(7.0f);
    REQUIRE(v.GetY() == 7.0f);

    v.Set(1.0f, 2.0f);
    REQUIRE(v.GetX() == 1.0f);
    REQUIRE(v.GetY() == 2.0f);
}

TEST_CASE("Display reports its dimensions and resizes cleanly",
          "[Display]")
{
    Display d(64, 48);
    REQUIRE(d.GetWidth() == 64);
    REQUIRE(d.GetHeight() == 48);
    REQUIRE(d.GetDisplayRGBAData() != nullptr);

    d.Resize(128, 96);
    REQUIRE(d.GetWidth() == 128);
    REQUIRE(d.GetHeight() == 96);
    REQUIRE(d.GetDisplayRGBAData() != nullptr);
}

TEST_CASE("Display default DoDrawFrame draws fallback diamond",
          "[Display]")
{
    constexpr int w = 600;
    constexpr int h = 300;
    Display d(w, h);

    d.DoDrawFrame(0.016f);

    const uchar* data = d.GetDisplayRGBAData();
    REQUIRE(AlphaByteAt(data, 300, 150, w) == 255);
    REQUIRE(AlphaByteAt(data, 10, 10, w) == 0);
    REQUIRE(AlphaByteAt(data, 300, 250, w) == 0);
}

TEST_CASE("Display SetScene routes DoDrawFrame to the scene",
          "[Display]")
{
    constexpr int w = 100;
    constexpr int h = 100;
    Display d(w, h);

    d.SetScene(std::shared_ptr<SWR::Scene>(new FillShapeScene()));
    d.DoDrawFrame(0.016f);

    const uchar* data = d.GetDisplayRGBAData();
    REQUIRE(AlphaByteAt(data, 0, 0, w) == 28);
}

TEST_CASE("DisplayFactory returns a configured display",
          "[DisplayFactory]")
{
    auto d = DisplayFactory::GetConfiguredDisplay(400, 320);
    REQUIRE(d != nullptr);
    REQUIRE(d->GetWidth() == 400);
    REQUIRE(d->GetHeight() == 320);
    REQUIRE(d->GetDisplayRGBAData() != nullptr);

    d->DoDrawFrame(0.016f);
    REQUIRE(d->GetDisplayRGBAData() != nullptr);
}
