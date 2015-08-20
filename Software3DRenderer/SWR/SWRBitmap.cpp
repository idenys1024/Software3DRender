//
//  SWRBitmap.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "SWRBitmap.h"
#include <cstring>

SWRBitmap::SWRBitmap(int width, int height, SWRBitmapColorSpace colorSpace)
{
    _width=width;
    _height=height;
    _colorSpace=colorSpace;
    _numOfComponents=4;
    _components=new uchar[SizeOfComponents()];
}

SWRBitmap::~SWRBitmap()
{
    delete [] _components;
}

void SWRBitmap::Clear(uchar shade)
{
    memset(_components, shade, SizeOfComponents());
}

void SWRBitmap::DrawPixel(int pX,int pY,uchar a,uchar b,uchar g,uchar r)
{
    if(pX>=_width||pY>=_height)
        return;
    
    int index=(pX+pY*_width)*_numOfComponents;
    switch (_colorSpace) {
        case SWRBITMAP_ABGR:
            _components[index  ]=a;
            _components[index+1]=b;
            _components[index+2]=g;
            _components[index+3]=r;
            
            break;
        case SWRBITMAP_RGBA:
            _components[index  ]=r;
            _components[index+1]=g;
            _components[index+2]=b;
            _components[index+3]=a;
            break;
        default:
            
            break;
    }

}

int SWRBitmap::SizeOfComponents()
{
    return _width*_height*_numOfComponents;
}

const uchar** const SWRBitmap::GetComponentsData() const
{
    return (const uchar** const)(&_components);
}


