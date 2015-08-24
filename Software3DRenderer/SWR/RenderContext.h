//
//  SWRRenderContext.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/20/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#ifndef __Software3DRenderer__SWRRenderContext__
#define __Software3DRenderer__SWRRenderContext__

#include <stdio.h>
#include "Bitmap.h"
#include "Vertex.h"

namespace SWR{
    
class RenderContext: public Bitmap
{
public:
    RenderContext(int w, int h);
    virtual ~RenderContext();
    void DrawScanBuffer(int yCoord, int xMin, int xMax);
    void FillShape(int yMin, int yMax);
    void ScanConvertTriangle(Vertex minYv, Vertex midYv, Vertex maxYv, int side);
protected:
    void ScanConvertLine(Vertex minY,Vertex maxY,int side);
    int* _scanBuffer;
};
    
}
#endif /* defined(__Software3DRenderer__SWRRenderContext__) */
