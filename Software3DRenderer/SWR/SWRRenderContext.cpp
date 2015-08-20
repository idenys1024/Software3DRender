//
//  SWRRenderContext.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "SWRRenderContext.h"


SWRRenderContext::SWRRenderContext(int w, int h):SWRBitmap(w,h,SWRBITMAP_RGBA)
{
    _scanBuffer=new int[h*2];
}

SWRRenderContext::~SWRRenderContext()
{
    delete [] _scanBuffer;
}

void SWRRenderContext::DrawScanBuffer(int yCoord, int xMin, int xMax)
{
    if(yCoord>=_height)
        return;
    
    _scanBuffer[yCoord*2  ]=xMin;
    _scanBuffer[yCoord*2+1]=xMax;
}

void SWRRenderContext::FillShape(int yMin, int yMax)
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
