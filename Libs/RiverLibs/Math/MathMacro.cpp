//
//  MathMacro.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/10.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "stdinc.h"
#include "MathMacro.h"

namespace  MathFunc
{
    bool Approximately(float a,float b)
    {
        float diff = fabsf(a-b);
        if(diff < MATH_EPSILON)
            return true;
        
        return false;
    }
}
