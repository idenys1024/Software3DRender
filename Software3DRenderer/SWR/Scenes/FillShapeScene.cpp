//
//  FillShapeScene.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/21/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "FillShapeScene.h"


void FillShapeScene::UpdateAndDraw(float deltatime, std::shared_ptr<SWR::RenderContext> renderTarget)
{
    renderTarget->Clear(28);
    for(int j=200;j<300;j++)
        renderTarget->DrawScanBuffer(j, 300-j+50, 300+j);
    
    renderTarget->FillShape(200, 300);
}