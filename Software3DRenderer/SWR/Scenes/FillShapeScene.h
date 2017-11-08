//
//  FillShapeScene.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/21/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#ifndef __Software3DRenderer__FillShapeScene__
#define __Software3DRenderer__FillShapeScene__

#include "Scene.h"

class FillShapeScene: public SWR::Scene
{
public:
    //FillShapeScene();
    //~FillShapeScene();
    virtual void UpdateAndDraw(float deltatime, std::shared_ptr<SWR::RenderContext> renderTarget) override;
protected:
    
};

#endif /* defined(__Software3DRenderer__FillShapeScene__) */
