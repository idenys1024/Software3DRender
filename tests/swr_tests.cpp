#include <catch2/catch_test_macros.hpp>

#include <random>

#include "Bitmap.h"
#include "RenderContext.h"

using SWR::Bitmap;
using SWR::BITMAP_ABGR;
using SWR::BITMAP_RGBA;
using SWR::RenderContext;
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
