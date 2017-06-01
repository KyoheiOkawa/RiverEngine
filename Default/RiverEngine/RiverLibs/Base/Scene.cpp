//
//  Scene.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene()
{
    
}

Scene::~Scene()
{
    
}

Scene* Scene::create()
{
    auto ret = new Scene();
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool Scene::init()
{
    return true;
}
