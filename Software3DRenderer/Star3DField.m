//
//  Star3DField.m
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/18/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import "Star3DField.h"
#import "SWRBitmap.h"

@interface Star3DField()
{

}
@property(nonatomic) float speed;
@property(nonatomic) float spread;
@property(nonatomic,strong) NSMutableArray* starX;
@property(nonatomic,strong) NSMutableArray* starY;
@property(nonatomic,strong) NSMutableArray* starZ;

@end

@implementation Star3DField

-(instancetype) initWithNimOfStars:(int) numStars
                            spread:(float) spread
                             speed:(float) speed
{
    self=[super init];
    if(self)
    {
        _speed=speed;
        _spread=spread;
        _starX=[NSMutableArray arrayWithCapacity:numStars];
        _starY=[NSMutableArray arrayWithCapacity:numStars];
        _starZ=[NSMutableArray arrayWithCapacity:numStars];
        for(int i=0;i<numStars;i++)
            [self initStarAtIndex:i];
    }
    return self;
}

-(void) initStarAtIndex:(int) index
{
    self.starX[index]=[NSNumber numberWithFloat:[self randomFloatBetween:-1.0f and:1.0f]*self.spread];
    self.starY[index]=[NSNumber numberWithFloat:[self randomFloatBetween:-1.0f and:1.0f]*self.spread];
    self.starZ[index]=[NSNumber numberWithFloat:[self randomFloatBetween:0.0f and:0.5f]*self.spread];
}

-(void) updateAndRenderOnBitmap:(SWRBitmap*) target withDeltaTime:(float) delta
{
    [target clear:0];
    CGSize targetSize=[target getSize];
    float halfWidth=targetSize.width*0.5f;
    float halfHeight=targetSize.height*0.5f;
     for(int i=0;i<[self.starX count];i++)
     {
         float curZ=[self.starZ[i] floatValue];
         self.starZ[i]=@(curZ-delta*self.speed);
         if([self.starZ[i] floatValue]<0)
             [self initStarAtIndex:i];
         
         int x=(int) (([self.starX[i] floatValue]/[self.starZ[i] floatValue])*halfWidth + halfWidth);
         int y=(int) (([self.starY[i] floatValue]/[self.starZ[i] floatValue])*halfHeight + halfHeight);
         
         if((x<=0 || x>=(int)targetSize.width) ||
            (y<=0 || y>=(int)targetSize.height))
         {
             [self initStarAtIndex:i];
         }
         else
         {
             [target drawPixelAtpX:x pY:y withA:255 B:255 G:255 R:255];
         }
     }
}


-(float)randomFloatBetween:(float)num1 and:(float)num2
{
    return ((float)arc4random() / RAND_MAX) * (num2 - num1) + num1;
}


@end
