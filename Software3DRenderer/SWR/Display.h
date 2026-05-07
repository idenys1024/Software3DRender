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

namespace SWR {
    
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
protected:
    std::shared_ptr<RenderContext> _frameBuffer;
    std::shared_ptr<Scene> _currentScene;
};
}
#endif /* defined(__Software3DRenderer__SWRDisplay__) */
