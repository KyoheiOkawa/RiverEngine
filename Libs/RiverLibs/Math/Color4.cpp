//
//  Color4.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/12.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Color4.hpp"

Color4::Color4()
{
    r = 1.0f;
    g = 1.0f;
    b = 1.0f;
    a = 1.0f;
}

Color4::Color4(float vr,float vg,float vb,float va)
{
    r = vr;
    g = vg;
    b = vb;
    a = va;
}

Color4& Color4::operator=(const Color4& other)
{
    if(this != &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }
    
    return *this;
}
