//
//  Bitmap.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 6/22/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef unsigned char uchar;
enum SWRBitmapColorSpace{
    SWRBITMAP_RGBA,
    SWRBITMAP_ABGR
};

@interface SWRBitmap : NSObject
-(instancetype) initWithWidth:(int) w height:(int) h colorSpace:(enum SWRBitmapColorSpace) cs;
-(void) clear:(unsigned char) shade;
-(void) drawPixelAtpX:(NSUInteger) x
                   pY:(NSUInteger) y
                withA:(uchar) a
                    B:(uchar) b
                    G:(uchar) g
                    R:(uchar) r;
-(void) copyToByteArray:(uchar*) dest; //copy from abgr to bgr
-(CGSize) getSize;
-(const uchar** const) data;
@end
