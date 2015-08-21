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
#include "SWRBitmap.h"

class SWRRenderContext: public SWRBitmap
{
public:
    SWRRenderContext(int w, int h);
    virtual ~SWRRenderContext();
    void DrawScanBuffer(int yCoord, int xMin, int xMax);
    void FillShape(int yMin, int yMax);
protected:
    int* _scanBuffer;
};

#endif /* defined(__Software3DRenderer__SWRRenderContext__) */
