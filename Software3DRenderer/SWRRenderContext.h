//
//  SWRRenderContext.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/19/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#import "SWRBitmap.h"

@interface SWRRenderContext : SWRBitmap


-(instancetype) initWithWidth:(int) w height:(int) h;
-(void) fillShapeWithYMin:(int) ymin yMax:(int) ymax;
-(void) drawScanBufferAtY:(int) yCoord xMin:(int)xmin xMax:(int) xmax;

@end
