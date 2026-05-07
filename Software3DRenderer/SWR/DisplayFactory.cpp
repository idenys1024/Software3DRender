//
//  DisplayFactory.cpp
//  Software3DRenderer
//
//  Created by Denis Kunitski on 8/21/15.
//  Copyright (c) 2015 Denis Kunitski. All rights reserved.
//

#include "DisplayFactory.h"
#include "Star3DFieldScene.h"
#include "FillShapeScene.h"
#include "TrianglesScene.h"
using namespace SWR;
std::shared_ptr<Display> DisplayFactory::GetConfiguredDisplay(int w,int h)
{
    std::shared_ptr<Display> display(new Display(w,h));
    display->AddScene(std::make_shared<Star3DFieldScene>(100000,40.0f,60.0f,5.0f));
    display->AddScene(std::make_shared<TrianglesScene>());
    display->AddScene(std::make_shared<FillShapeScene>());
    return display;
}
