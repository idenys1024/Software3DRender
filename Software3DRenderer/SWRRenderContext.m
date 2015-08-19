//
//  SWRRenderContext.m
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/19/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import "SWRRenderContext.h"
@interface SWRRenderContext()
{
    int* _scanBuffer;
}
@end

@implementation SWRRenderContext

-(instancetype) initWithWidth:(int) w height:(int) h
{
    self=[super initWithWidth:w height:h colorSpace:SWRBITMAP_RGBA];
    if(self)
    {
        _scanBuffer=malloc(sizeof(int)*h*2);
    }
    return self;
}

-(void) dealloc
{
    free(_scanBuffer);
}

-(void) drawScanBufferAtY:(int) yCoord xMin:(int)xmin xMax:(int) xmax
{
    if(yCoord>=[self getSize].height)
        return;
    
    _scanBuffer[yCoord*2  ]=xmin;
    _scanBuffer[yCoord*2+1]=xmax;
}

-(void) fillShapeWithYMin:(int) ymin yMax:(int) ymax
{
    for (int j=ymin; j<ymax; j++)
    {
        int xMin=_scanBuffer[j*2  ];
        int xMax=_scanBuffer[j*2+1];
        for (int i=xMin;i<xMax;i++)
        {
            [self drawPixelAtpX:i pY:j withA:255 B:255 G:255 R:255];
        }
    }
}


@end
