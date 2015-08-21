//
//  DisplayFactory.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/21/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "DisplayFactory.h"
#include "Star3DFieldScene.h"
#include "FillShapeScene.h"
#include "TrianglesScene.h"
using namespace SWR;
std::shared_ptr<Display> DisplayFactory::GetConfiguredDisplay(int w,int h)
{
    std::shared_ptr<Display> display(new Display(w,h));
    //display->SetScene(std::shared_ptr<Scene>(new Scene()));
    //display->SetScene(std::shared_ptr<Scene>(new Star3DFieldScene(1000,20.0f,60.0f,5.0f)));
    //display->SetScene(std::shared_ptr<Scene>(new FillShapeScene()));
    display->SetScene(std::shared_ptr<Scene>(new TrianglesScene()));
    
    return display;
}
