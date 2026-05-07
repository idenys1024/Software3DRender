//
//  DisplayFactory.h
//  Software3DRenderer
//
//  Created by Denis Kunitski on 8/21/15.
//  Copyright (c) 2015 Denis Kunitski. All rights reserved.
//

#ifndef __Software3DRenderer__DisplayFactory__
#define __Software3DRenderer__DisplayFactory__

#include <memory>
#include "Display.h"
namespace SWR
{
class DisplayFactory
{
public:
    static std::shared_ptr<Display> GetConfiguredDisplay(int w,int h);
    
};
}

#endif /* defined(__Software3DRenderer__DisplayFactory__) */
