//
//  Color4.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/12.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Color4_hpp
#define Color4_hpp

#include "stdinc.h"

class Color4
{
public:
    float r,g,b,a;
    
    Color4();
    Color4(float vr,float vg,float vb,float va);
    ~Color4(){}
    
    Color4& operator=(const Color4& other);
};

#endif /* Color4_hpp */
