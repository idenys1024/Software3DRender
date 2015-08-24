//
//  SWRDisplay.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "Display.h"
#include "RenderContext.h"
#include "Scene.h"

using namespace SWR;

Display::Display(int w,int h)
{
    _frameBuffer.reset(new RenderContext(w,h));
}

Display::~Display()
{
    
}

void Display::Resize(int newW, int newH)
{
    _frameBuffer.reset(new RenderContext(newW,newH));
}

void Display::DoDrawFrame(float deltaTime)
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

void Display::SwapBuffers()
{
    //nothing for now
}

const unsigned char* const Display::GetDisplayRGBAData() const
{
    return _frameBuffer->GetComponentsData();
}

int Display::GetWidth() const
{
    return _frameBuffer->GetWidth();
}

int Display::GetHeight() const
{
    return _frameBuffer->GetHeight();
}

void Display::SetScene(std::shared_ptr<Scene> newScene)
{
    _currentScene=newScene;
}

