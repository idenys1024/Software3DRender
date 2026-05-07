//
//  SWRDisplay.cpp
//  Software3DRenderer
//
//  Created by Denis Kunitski on 8/20/15.
//  Copyright (c) 2015 Denis Kunitski. All rights reserved.
//

#include "Display.h"
#include "RenderContext.h"
#include "Scene.h"
#include "UI/SceneSelectorOverlay.h"

using namespace SWR;

Display::Display(int w,int h)
    : _currentIndex(0)
{
    _frameBuffer.reset(new RenderContext(w,h));
    _overlay.reset(new UI::SceneSelectorOverlay());
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
    if (!_scenes.empty())
    {
        auto& scene = _scenes[_currentIndex];
        scene->UpdateAndDraw(deltaTime, _frameBuffer);

        if (_scenes.size() >= 2 && _overlay)
            _overlay->Draw(*_frameBuffer, scene->GetName());
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
    _scenes.clear();
    _currentIndex = 0;
    if (newScene)
        _scenes.push_back(newScene);
}

void Display::AddScene(std::shared_ptr<Scene> newScene)
{
    if (newScene)
        _scenes.push_back(newScene);
}

void Display::NextScene()
{
    if (_scenes.empty()) return;
    _currentIndex = (_currentIndex + 1) % static_cast<int>(_scenes.size());
}

void Display::PrevScene()
{
    if (_scenes.empty()) return;
    int n = static_cast<int>(_scenes.size());
    _currentIndex = (_currentIndex - 1 + n) % n;
}

int Display::GetSceneCount() const
{
    return static_cast<int>(_scenes.size());
}

int Display::GetCurrentSceneIndex() const
{
    return _currentIndex;
}

void Display::HandleMouseClick(int x, int y)
{
    if (_scenes.size() < 2 || !_overlay) return;
    int hit = _overlay->HitTest(x, y);
    if (hit < 0) PrevScene();
    else if (hit > 0) NextScene();
}
