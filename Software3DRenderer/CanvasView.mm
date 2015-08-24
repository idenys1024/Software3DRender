//
//  CanvasView.m
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 6/22/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import "CanvasView.h"
#import "DisplayFactory.h"


@interface CanvasView()
@property(nonatomic) std::shared_ptr<SWR::Display> display;

@end
 
@implementation CanvasView

- (instancetype) initWithCoder:(NSCoder *)coder
{
    self=[super initWithCoder:coder];
    if(self)
    {
        _display=SWR::DisplayFactory::GetConfiguredDisplay((int)self.frame.size.width, (int)self.frame.size.height);
       
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

-(void) onFrameSizeChange:(NSNotification*) n
{
    if(!CGSizeEqualToSize(CGSizeMake(_display->GetWidth(), _display->GetHeight()),self.frame.size))
    {
        _display->Resize((int)self.frame.size.width,(int)self.frame.size.height);
       // NSLog (@"resize display: %f, %f", self.frame.size.width, self.frame.size.height);
    }
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
   
    _display->DoDrawFrame(_deltaTime);
    _display->SwapBuffers();
    [self reflectSWRDisplayToView];
  }

-(void)reflectSWRDisplayToView
{
    CGSize displaySize=CGSizeMake(_display->GetWidth(), _display->GetHeight());
    NSRect drawRect=NSMakeRect(0, 0, displaySize.width, displaySize.height);
    const unsigned char* const bitmapData[5]={_display->GetDisplayRGBAData(),NULL,NULL,NULL,NULL};
    NSDrawBitmap(drawRect,
                 (int)displaySize.width,
                 (int)displaySize.height,
                 8,
                 4,
                 32,
                 (7 + ((int)displaySize.width * 32)) / 8,
                 NO,
                 YES,
                 NSDeviceRGBColorSpace,
                 bitmapData
                 );
}

@end
