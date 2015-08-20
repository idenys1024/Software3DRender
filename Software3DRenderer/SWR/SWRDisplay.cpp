//
//  SWRDisplay.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "SWRDisplay.h"
#include "SWRRenderContext.h"

SWRDisplay::SWRDisplay(int w,int h)
{
    _frameBuffer=new SWRRenderContext(w,h);
}

SWRDisplay::~SWRDisplay()
{
    
}

void SWRDisplay::Resize(int newW, int newH)
{
    delete _frameBuffer;
    _frameBuffer=new SWRRenderContext(newW,newH);
}

void SWRDisplay::DoDrawFrame(float deltaTime)
{
    _frameBuffer->Clear(0);
    for(int j=100;j<200;j++)
    {
        _frameBuffer->DrawScanBuffer(j, 300-j, 300+j);
    }
    
    _frameBuffer->FillShape(100, 200);
}

void SWRDisplay::SwapBuffers()
{
    //nothing for now
}

const unsigned char* const SWRDisplay::GetDisplayRGBAData() const
{
    return _frameBuffer->GetComponentsData();
}

int SWRDisplay::GetWidth() const
{
    return _frameBuffer->GetWidth();
}

int SWRDisplay::GetHeight() const
{
    return _frameBuffer->GetHeight();
}

