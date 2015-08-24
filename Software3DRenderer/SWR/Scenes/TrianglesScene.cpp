//
//  TrianglesScene.cpp
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/21/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#include "TrianglesScene.h"
using namespace SWR;
void TrianglesScene::UpdateAndDraw(float deltatime, std::shared_ptr<RenderContext> renderTarget)
{
    renderTarget->Clear(0);
    
    Vertex minY=Vertex(100,100);
    Vertex midY=Vertex(150,200);
    Vertex maxY=Vertex(40,300);
    renderTarget->ScanConvertTriangle(minY, midY, maxY, 0);
    renderTarget->FillShape(100, 300);
}

