//
//  Star3DFieldScene.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "Star3DFieldScene.h"
#include <math.h>

Star3DFieldScene::Star3DFieldScene(int numOfStars, float speed, float spread):SWRScene()
{
    _speed=speed;
    _spread=spread;
    _starPositions.resize(numOfStars);
    for(StarsVct::iterator ii=_starPositions.begin();ii!=_starPositions.end();ii++)
        InitStar(ii);
}

Star3DFieldScene::~Star3DFieldScene()
{
    
}

float Star3DFieldScene::Random(float num1 ,float num2) const
{
    return ((float)rand() / RAND_MAX) * (num2 - num1) + num1;
}

void Star3DFieldScene::InitStar(StarsVct::iterator ii)
{
    StarPosition& sp=*ii;
    sp.x=Random(-1.0f, 1.0f)*_spread;
    sp.y=Random(-1.0f, 1.0f)*_spread;
    sp.z=Random(0.0f, 1.5f)*_spread;
}

void Star3DFieldScene::UpdateAndDraw(float deltatime, std::shared_ptr<SWRRenderContext> renderTarget)
{
    renderTarget->Clear(0);
    
    float halfWidth=renderTarget->GetWidth()*0.5f;
    float halfHeight=renderTarget->GetHeight()*0.5f;
    float FOVinDegree=90.0f;
    float tanHalfFOV=tanf((FOVinDegree*0.5)*(M_PI/180.0));
    
    int w=renderTarget->GetWidth();
    int h=renderTarget->GetHeight();
    for(StarsVct::iterator ii=_starPositions.begin();ii!=_starPositions.end();ii++)
    {
        StarPosition& cs=*ii;
        cs.z=cs.z-deltatime*_speed;
        
        if(cs.z<0)
        {
            InitStar(ii);
            continue;
        }
        
        int x=(int) ((cs.x/(cs.z*tanHalfFOV))*halfWidth + halfWidth);
        int y=(int) ((cs.y/(cs.z*tanHalfFOV))*halfHeight + halfHeight);
        
        if((x<=0 || x>=(int)w) ||
           (y<=0 || y>=(int)h))
        {
            InitStar(ii);
        }
        else
        {
            renderTarget->DrawPixel(x, y, 255, 255, 255, 255);
        }
    }
}