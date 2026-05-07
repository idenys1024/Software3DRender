//
//  FillShapeScene.h
//  Software3DRenderer
//
//  Created by Denis Kunitski on 8/21/15.
//  Copyright (c) 2015 Denis Kunitski. All rights reserved.
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
    virtual const char* GetName() const override { return "FILLSHAPE"; }
protected:
    
};

#endif /* defined(__Software3DRenderer__FillShapeScene__) */
