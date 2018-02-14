//
//  Transform.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/19.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "stdinc.h"
#include "river.h"


Transform::Transform(const std::shared_ptr<GameObject>& GameObjectPtr):
Component(GameObjectPtr),
_scale(Vector3::ONE()),
_position(Vector3::ZERO()),
_pivot(Vector3(0.5f,0.5f,0.5f))
{
    
}

Transform::~Transform()
{
    
}
