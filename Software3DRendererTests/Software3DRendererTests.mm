//
//  Software3DRendererTests.m
//  Software3DRendererTests
//
//  Created by Denys Kunytskyi on 6/22/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import "SWRBitmap.h"

@interface Software3DRendererTests : XCTestCase

@end

@implementation Software3DRendererTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}
/*
- (void)testExample {
    // This is an example of a functional test case.
    XCTAssert(YES, @"Pass");
}
*/
- (void)testBitmap {
    
    int minTestW=10;
    int minTestH=10;
    int maxTestW=2048;
    int maxTestH=2048;
    int w=minTestW+arc4random()%(maxTestW-minTestW);
    int h=minTestH+arc4random()%(maxTestH-minTestH);
    SWRBitmap bitMap(w,h,SWRBITMAP_ABGR);
    uchar clearVal=arc4random()%255;
    bitMap.Clear(clearVal);
    //bitMap.DrawPixel(0, 0, 200, 200, 200, 200);
    for(int i=0;i<w*h*4;i++)
        XCTAssert(bitMap.GetComponentsData()[i]==clearVal, @"Bitmap clear fail ex=%d, equ=%d",clearVal,bitMap.GetComponentsData()[i]);
    
    for(int i=0;i<25;i++)
    {
        uchar a=arc4random()%255;
        uchar b=arc4random()%255;
        uchar g=arc4random()%255;
        uchar r=arc4random()%255;
        int px=arc4random()%w;
        int py=arc4random()%h;
        int index=(px+py*w)*4;
        bitMap.DrawPixel(px, py, a, b, g, r);
        XCTAssert(bitMap.GetComponentsData()[index]==a, @"Bitmap DrawPixel fail ex=%d, equ=%d",a,bitMap.GetComponentsData()[index]);
        XCTAssert(bitMap.GetComponentsData()[index+1]==b, @"Bitmap DrawPixel fail ex=%d, equ=%d",b,bitMap.GetComponentsData()[index+1]);
        XCTAssert(bitMap.GetComponentsData()[index+2]==g, @"Bitmap DrawPixel fail ex=%d, equ=%d",g,bitMap.GetComponentsData()[index+2]);
        XCTAssert(bitMap.GetComponentsData()[index+3]==r, @"Bitmap DrawPixel fail ex=%d, equ=%d",r,bitMap.GetComponentsData()[index+3]);
    }
    
    for(int i=0;i<25;i++)//tests for RGBA space
    {
        SWRBitmap bitMap(w,h,SWRBITMAP_RGBA);
        uchar a=arc4random()%255;
        uchar b=arc4random()%255;
        uchar g=arc4random()%255;
        uchar r=arc4random()%255;
        int px=arc4random()%w;
        int py=arc4random()%h;
        int index=(px+py*w)*4;
        bitMap.DrawPixel(px, py, a, b, g, r);
        XCTAssert(bitMap.GetComponentsData()[index+3]==a, @"Bitmap DrawPixel fail ex=%d, equ=%d",a,bitMap.GetComponentsData()[index+3]);
        XCTAssert(bitMap.GetComponentsData()[index+2]==b, @"Bitmap DrawPixel fail ex=%d, equ=%d",b,bitMap.GetComponentsData()[index+2]);
        XCTAssert(bitMap.GetComponentsData()[index+1]==g, @"Bitmap DrawPixel fail ex=%d, equ=%d",g,bitMap.GetComponentsData()[index+1]);
        XCTAssert(bitMap.GetComponentsData()[index+0]==r, @"Bitmap DrawPixel fail ex=%d, equ=%d",r,bitMap.GetComponentsData()[index+0]);
    }
}
/*
- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}
*/
@end
