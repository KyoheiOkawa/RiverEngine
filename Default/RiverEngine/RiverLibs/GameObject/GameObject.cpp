//
//  GameObject.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject()
{
    
}

GameObject::~GameObject()
{
    
}

GameObject* GameObject::create()
{
    auto ret = new (std::nothrow) GameObject();
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}
