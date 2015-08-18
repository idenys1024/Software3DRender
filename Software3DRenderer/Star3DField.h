//
//  Star3DField.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/18/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import <Foundation/Foundation.h>
@class SWRBitmap;
@interface Star3DField : NSObject
-(instancetype) initWithNimOfStars:(int) numStars
                            spread:(float) spread
                             speed:(float) speed;

-(void) updateAndRenderOnBitmap:(SWRBitmap*) target withDeltaTime:(float) delta;
@end
