//
//  CanvasView.m
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 6/22/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import "CanvasView.h"
#import "SWRRenderContext.h"
#import "Star3DField.h"

@interface CanvasView()
@property(strong,nonatomic) SWRBitmap *testBitmap;
@property(strong,nonatomic) SWRRenderContext *frameBuffer;
@property(strong,nonatomic) Star3DField *star3DField;

@end

@implementation CanvasView

- (instancetype) initWithCoder:(NSCoder *)coder
{
    self=[super initWithCoder:coder];
    if(self)
    {
        [self reinitFrameBuffer];
        NSLog (@"_frameBuffer: %f, %f", self.frame.size.width, self.frame.size.height);
        _star3DField=[[Star3DField alloc] initWithNimOfStars:4096 spread:64.0f speed:20.0f];
        
        [[NSNotificationCenter defaultCenter]	addObserver:self
                                                 selector:@selector(onFrameSizeChange:)
                                                     name:NSViewFrameDidChangeNotification
                                                   object:nil
         ];
    }
    return self;
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

-(void) reinitFrameBuffer
{
    _frameBuffer=[[SWRRenderContext alloc] initWithWidth:(int)self.frame.size.width
                                                  height:(int)self.frame.size.height];
}

-(void) onFrameSizeChange:(NSNotification*) n
{
    if(!CGSizeEqualToSize([_frameBuffer getSize],self.frame.size))
    {
       // NSLog (@"reinit frame buffer: %f, %f", self.frame.size.width, self.frame.size.height);
        [self reinitFrameBuffer];
    }
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
   
    //[self.star3DField updateAndRenderOnBitmap:self.frameBuffer withDeltaTime:self.deltaTime];
    [self.frameBuffer clear:0];
    for(int j=100;j<200;j++)
    {
        [self.frameBuffer drawScanBufferAtY:j xMin:300-j xMax:300+j];
    }
    
    [self.frameBuffer fillShapeWithYMin:100 yMax:200];
    
    [self swapBuffers];
  }

-(void)swapBuffers
{
    CGSize frameBufSize=[_frameBuffer getSize];
    NSRect drawRect=NSMakeRect(0, 0, frameBufSize.width, frameBufSize.height);
    NSDrawBitmap(drawRect,
                 (int)frameBufSize.width,
                 (int)frameBufSize.height,
                 8,
                 4,
                 32,
                 (7 + ((int)frameBufSize.width * 32)) / 8,
                 NO,
                 YES,
                 NSDeviceRGBColorSpace,
                 [_frameBuffer componentsData]
                 );

}

@end
