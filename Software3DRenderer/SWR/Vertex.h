//
//  Vertex.h
//  Software3DRenderer
//
//  Created by Denys Kunytskyi on 8/21/15.
//  Copyright (c) 2015 Denys Kunytskyi. All rights reserved.
//

#ifndef __Software3DRenderer__Vertex__
#define __Software3DRenderer__Vertex__

#include <stdio.h>
namespace SWR{
    class Vertex
    {
    public:
        Vertex():_x(0),_y(0){}
        Vertex(float x,float y){Set(x,y);}
        float GetX() const{return _x;}
        float GetY() const{return _y;}
        void Set(float x,float y){_x=x; _y=y;}
        void SetX(float x){_x=x;}
        void SetY(float y){_y=y;}
        
    protected:
        float _x;
        float _y;
    };
}
#endif /* defined(__Software3DRenderer__Vertex__) */
