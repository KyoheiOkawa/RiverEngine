//
//  Project.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/03.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Project_hpp
#define Project_hpp

#include "river.h"

struct PhysicParam
{
    Vector3 _velocity;
    float _friction;
    
    PhysicParam():
    _velocity(Vector3(0,0,0)),
    _friction(0.95f)
    {
    }
};

#endif /* Project_hpp */
