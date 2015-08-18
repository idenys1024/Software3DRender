//
//  ViewController.m
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 6/22/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import "ViewController.h"

@interface ViewController()
{
    CVDisplayLinkRef displayLink;
    
}
@property (strong) IBOutlet CanvasView *canvasView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    
    CGDirectDisplayID   displayID = CGMainDisplayID();
    CVReturn            error = kCVReturnSuccess;
    error = CVDisplayLinkCreateWithCGDisplay(displayID, &displayLink);
    if (error)
    {
        NSLog(@"DisplayLink created with error:%d", error);
        displayLink = NULL;
    }
    CVDisplayLinkSetOutputCallback(displayLink, renderCallback, (__bridge void *)self);
     NSLog(@"viewDidLoad");

   
    // Do any additional setup after loading the view.
}

static CVReturn renderCallback(CVDisplayLinkRef displayLink,
                               const CVTimeStamp *inNow,
                               const CVTimeStamp *inOutputTime,
                               CVOptionFlags flagsIn,
                               CVOptionFlags *flagsOut,
                               void *displayLinkContext)
{
    NSTimeInterval deltaTime = 1.0 / (inOutputTime->rateScalar * (double)inOutputTime->videoTimeScale / (double)inOutputTime->videoRefreshPeriod);
    [(__bridge ViewController *)displayLinkContext renderLoop:deltaTime];
    return kCVReturnSuccess;//
}

-(void) renderLoop:(NSTimeInterval) deltaTime
{
    self.canvasView.deltaTime=deltaTime;
    self.canvasView.needsDisplay=YES;
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

-(void) viewDidAppear
{
     CVDisplayLinkStart(displayLink);
}

-(void) viewDidDisappear
{
    CVDisplayLinkStop(displayLink);
    CVDisplayLinkRelease(displayLink);
    displayLink=NULL;
}



@end
