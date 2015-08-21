//
//  SWRDisplay.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "SWRDisplay.h"
#include "SWRRenderContext.h"
#include "SWRScene.h"



SWRDisplay::SWRDisplay(int w,int h)
{
    _frameBuffer.reset(new SWRRenderContext(w,h));
}

SWRDisplay::~SWRDisplay()
{
    
}

void SWRDisplay::Resize(int newW, int newH)
{
    _frameBuffer.reset(new SWRRenderContext(newW,newH));
}

void SWRDisplay::DoDrawFrame(float deltaTime)
{
    
    if(_currentScene!=nullptr)
    {
        _currentScene->UpdateAndDraw(deltaTime, _frameBuffer);
    }
    else
    {
        _frameBuffer->Clear(0);
        for(int j=100;j<200;j++)
        {
            _frameBuffer->DrawScanBuffer(j, 300-j, 300+j);
        }
        
        _frameBuffer->FillShape(100, 200);
    }
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

void SWRDisplay::SetScene(std::shared_ptr<SWRScene> newScene)
{
    _currentScene=newScene;
}

