//
//  Star3DFieldScene.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#ifndef __Software3DRenderer__Star3DFieldScene__
#define __Software3DRenderer__Star3DFieldScene__

#include <stdio.h>
#include "Scene.h"
#include <vector>

class Star3DFieldScene: public SWR::Scene
{
public:
    Star3DFieldScene(int numOfStars, float speed, float spread, float acceleration=0.0f);
    ~Star3DFieldScene();
    virtual void UpdateAndDraw(float deltatime, std::shared_ptr<SWR::RenderContext> renderTarget) override;
protected:
    struct StarPosition
    {
        float x;
        float y;
        float z;
        unsigned char bright;
    };
    float _speed;
    float _spread;
    float _acceleration;
    typedef std::vector<StarPosition> StarsVct;
    StarsVct _starPositions;
    void InitStar(StarsVct::iterator ii);
    float Random(float num1, float num2) const;
};
#endif /* defined(__Software3DRenderer__Star3DFieldScene__) */
