//
//  SWRRenderContext.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "RenderContext.h"
using namespace SWR;

RenderContext::RenderContext(int w, int h):Bitmap(w,h,BITMAP_RGBA)
{
    _scanBuffer=new int[h*2];
}

RenderContext::~RenderContext()
{
    delete [] _scanBuffer;
}

void RenderContext::DrawScanBuffer(int yCoord, int xMin, int xMax)
{
    if(yCoord>=_height)
        return;
    
    _scanBuffer[yCoord*2  ]=xMin;
    _scanBuffer[yCoord*2+1]=xMax;
}

void RenderContext::FillShape(int yMin, int yMax)
{
    for (int j=yMin; j<yMax; j++)
    {
        int xMin=_scanBuffer[j*2  ];
        int xMax=_scanBuffer[j*2+1];
        for (int i=xMin;i<xMax;i++)
        {
            DrawPixel(i, j, 255, 255, 255, 255);
        }
    }
}
