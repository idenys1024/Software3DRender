//
//  DisplayFactory.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/21/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "DisplayFactory.h"
#include "Star3DFieldScene.h"

std::shared_ptr<SWRDisplay> DisplayFactory::GetConfiguredDisplay(int w,int h)
{
    std::shared_ptr<SWRDisplay> display(new SWRDisplay(w,h));
    //display->SetScene(std::shared_ptr<SWRScene>(new SWRScene()));
    display->SetScene(std::shared_ptr<SWRScene>(new Star3DFieldScene(4000,20.0f,60.0f)));
    
    return display;
}
