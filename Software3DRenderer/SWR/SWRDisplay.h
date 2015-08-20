//
//  SWRDisplay.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#ifndef __Software3DRenderer__SWRDisplay__
#define __Software3DRenderer__SWRDisplay__

#include <stdio.h>
#include <memory>
class SWRRenderContext;
class SWRScene;
class SWRDisplay
{
public:
    SWRDisplay(int w,int h);
    virtual ~SWRDisplay();
    void Resize(int newW, int newH);
    void DoDrawFrame(float deltaTime);
    void SwapBuffers();
    const unsigned char* const GetDisplayRGBAData() const;
    int GetWidth() const;
    int GetHeight() const;
    void SetScene(std::shared_ptr<SWRScene> newScene);
protected:
    std::shared_ptr<SWRRenderContext> _frameBuffer;
    std::shared_ptr<SWRScene> _currentScene;
};
#endif /* defined(__Software3DRenderer__SWRDisplay__) */
