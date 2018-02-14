//
//  Component.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/11.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "stdinc.h"
#include "river.h"

Component::Component(const std::shared_ptr<GameObject>& GameObjectPtr):
_gameObject(GameObjectPtr)
{
    
}

Component::~Component()
{
    
}
