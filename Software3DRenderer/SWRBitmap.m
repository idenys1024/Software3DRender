//
//  Bitmap.m
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 6/22/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import "SWRBitmap.h"

@interface SWRBitmap()
{
    NSUInteger _width;
    NSUInteger _height;
    NSUInteger _numOfComponents;
    enum SWRBitmapColorSpace _colorSpace;
    unsigned char* _components;// store pixels in abgr format
}
@end

@implementation SWRBitmap

-(instancetype) initWithWidth:(int) w
                       height:(int) h
                   colorSpace:(enum SWRBitmapColorSpace) cs;
{
    self=[super init];
    if(self)
    {
        _colorSpace=cs;
        _width=w;
        _height=h;
        _numOfComponents=4;
        _components=malloc([self sizeOfComponents]);
    }
    
    return self;
}

-(NSUInteger) sizeOfComponents
{
    return _width*_height*_numOfComponents;
}

-(void) dealloc
{
    free(_components);
}

-(void) clear:(uchar) shade
{
    for(NSUInteger i=0;i<[self sizeOfComponents];i++)
        _components[i]=shade;
}

-(void) drawPixelAtpX:(NSUInteger) x
                   pY:(NSUInteger) y
                withA:(uchar) a
                    B:(uchar) b
                    G:(uchar) g
                    R:(uchar) r

{
    NSInteger index=(x+y*_width)*_numOfComponents;
    switch (_colorSpace) {
        case SWRBITMAP_ABGR:
            _components[index  ]=a;
            _components[index+1]=b;
            _components[index+2]=g;
            _components[index+3]=r;
            
            break;
        case SWRBITMAP_RGBA:
            _components[index  ]=r;
            _components[index+1]=g;
            _components[index+2]=b;
            _components[index+3]=a;
            break;
        default:
            NSLog(@"SWRBitmap::drawPixelAt wrong color space");
            break;
    }
}

-(void) copyToByteArray:(uchar*) dest
{
    for(int i=0;i<_width*_height;i++)
    {
        dest[i*3    ]=_components[i*4 + 1];
        dest[i*3 + 1]=_components[i*4 + 2];
        dest[i*3 + 2]=_components[i*4 + 3];
    }
}

-(CGSize) getSize
{
    return CGSizeMake(_width, _height);
}

-(const uchar** const) data
{
    return (const uchar** const)(&_components);
}


@end
