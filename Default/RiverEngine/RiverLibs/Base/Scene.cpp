//
//  Scene.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "river.h"

Scene::Scene()
{
    
}

Scene::~Scene()
{
    
}

std::shared_ptr<Scene> Scene::create()
{
    auto ret = std::shared_ptr<Scene>(new Scene);
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

void Scene::draw()
{
    for(auto object : _gameObjects)
    {
        object->update();
        object->draw();
    }
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
    gameObject->setScene(getThis<Scene>());
    _gameObjects.push_back(gameObject);
}
