//
//  SWRScene.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "Scene.h"
#include "RenderContext.h"

using namespace SWR;

Scene::Scene()
{
    
}

Scene::~Scene()
{
    
}

void Scene::UpdateAndDraw(float deltatime, std::shared_ptr<RenderContext> renderTarget)
{
    int w=renderTarget->GetWidth();
    int h=renderTarget->GetHeight();
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            renderTarget->DrawPixel(i, j, 255, (i*j*i/h)%256, i%256, rand()%256);
        }
    }
}