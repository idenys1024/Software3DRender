//
//  SWRBitmap.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "Bitmap.h"
#include <cstring>
using namespace SWR;

Bitmap::Bitmap(int width, int height, BitmapColorSpace colorSpace)
{
    _width=width;
    _height=height;
    _colorSpace=colorSpace;
    _numOfComponents=4;
    _components=new uchar[SizeOfComponents()];
}

Bitmap::~Bitmap()
{
    delete [] _components;
}

void Bitmap::Clear(uchar shade)
{
    memset(_components, shade, SizeOfComponents());
}

void Bitmap::DrawPixel(int pX,int pY,uchar a,uchar b,uchar g,uchar r)
{
    if(pX>=_width||pY>=_height)
        return;
    
    int index=(pX+pY*_width)*_numOfComponents;
    switch (_colorSpace) {
        case BITMAP_ABGR:
            _components[index  ]=a;
            _components[index+1]=b;
            _components[index+2]=g;
            _components[index+3]=r;
            
            break;
        case BITMAP_RGBA:
            _components[index  ]=r;
            _components[index+1]=g;
            _components[index+2]=b;
            _components[index+3]=a;
            break;
        default:
            
            break;
    }
}

int Bitmap::SizeOfComponents() const
{
    return _width*_height*_numOfComponents;
}

int Bitmap::GetWidth() const
{
    return _width;
}

int Bitmap::GetHeight() const
{
    return _height;
}

const uchar* const Bitmap::GetComponentsData() const
{
    return _components;
}


