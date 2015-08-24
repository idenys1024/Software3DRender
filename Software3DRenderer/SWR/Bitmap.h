//
//  SWRBitmap.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#ifndef __Software3DRenderer__SWRBitmap__
#define __Software3DRenderer__SWRBitmap__

#include <stdio.h>


namespace SWR{

typedef unsigned char uchar;
enum BitmapColorSpace{
    BITMAP_RGBA,
    BITMAP_ABGR
};

class Bitmap
{
public:
    Bitmap(int width, int height, BitmapColorSpace colorSpace);
    virtual ~Bitmap();
    void Clear(uchar shade);
    void DrawPixel(int pX,int pY,uchar a,uchar b,uchar g,uchar r);
    const uchar* const GetComponentsData() const;
    int GetWidth() const;
    int GetHeight() const;
protected:
    int SizeOfComponents() const;
    int _width;
    int _height;
    int _numOfComponents;
    enum BitmapColorSpace _colorSpace;
    unsigned char* _components;// store pixels in abgr or rgba format
};
    
}

#endif /* defined(__Software3DRenderer__SWRBitmap__) */
