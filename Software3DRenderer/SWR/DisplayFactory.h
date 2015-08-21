//
//  DisplayFactory.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/21/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#ifndef __Software3DRenderer__DisplayFactory__
#define __Software3DRenderer__DisplayFactory__

#include <memory>
#include "SWRDisplay.h"

class DisplayFactory
{
public:
    static std::shared_ptr<SWRDisplay> GetConfiguredDisplay(int w,int h);
    
};


#endif /* defined(__Software3DRenderer__DisplayFactory__) */
