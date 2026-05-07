//
//  SWRDisplay.h
//  Software3DRenderer
//
//  Created by Denis Kunitski on 8/20/15.
//  Copyright (c) 2015 Denis Kunitski. All rights reserved.
//

#ifndef __Software3DRenderer__SWRDisplay__
#define __Software3DRenderer__SWRDisplay__

#include <stdio.h>
#include <memory>
#include <vector>

namespace SWR {

namespace UI { class SceneSelectorOverlay; }

class RenderContext;
class Scene;
class Display
{
public:
    static std::shared_ptr<Display> GetConfiguredDisplay(int w,int h);
    Display(int w,int h);
    virtual ~Display();
    void Resize(int newW, int newH);
    void DoDrawFrame(float deltaTime);
    void SwapBuffers();
    const unsigned char* const GetDisplayRGBAData() const;
    int GetWidth() const;
    int GetHeight() const;
    void SetScene(std::shared_ptr<Scene> newScene);
    void AddScene(std::shared_ptr<Scene> newScene);
    void NextScene();
    void PrevScene();
    int  GetSceneCount() const;
    int  GetCurrentSceneIndex() const;
    void HandleMouseClick(int x, int y);
protected:
    std::shared_ptr<RenderContext> _frameBuffer;
    std::vector<std::shared_ptr<Scene>> _scenes;
    int _currentIndex;
    std::unique_ptr<UI::SceneSelectorOverlay> _overlay;
};
}
#endif /* defined(__Software3DRenderer__SWRDisplay__) */
