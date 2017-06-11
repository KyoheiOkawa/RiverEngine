//
//  GameObject.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "river.h"

GameObject::GameObject()
{
    
}

GameObject::~GameObject()
{
    
}

std::shared_ptr<GameObject> GameObject::create()
{
    auto gameObject = new GameObject();
    auto ret = gameObject->getThis<GameObject>();
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}
