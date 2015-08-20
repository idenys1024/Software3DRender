//
//  SWRScene.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#ifndef __Software3DRenderer__SWRScene__
#define __Software3DRenderer__SWRScene__

#include <stdio.h>
#include <memory>
class SWRRenderContext;

class SWRScene
{
public:
    SWRScene();
    virtual ~SWRScene();
    virtual void UpdateAndDraw(float deltatime, std::shared_ptr<SWRRenderContext> renderTarget);
};
#endif /* defined(__Software3DRenderer__SWRScene__) */
