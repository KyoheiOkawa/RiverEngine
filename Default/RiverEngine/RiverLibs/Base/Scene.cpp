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

}

void Scene::gameObjectUpdate()
{
    for(auto& object : _gameObjects)
    {
        object->update();
    }
    
    //削除対象ゲームオブジェクトを削除
    if(_waitRemoveObjects.size() != 0)
    {
        for(auto& deleteObj : _waitRemoveObjects)
        {
            auto it = _gameObjects.begin();
            while(it != _gameObjects.end())
            {
                if(*it == deleteObj)
                {
                    _gameObjects.erase(it);
                    break;
                }
                it++;
            }
        }
        
        _waitRemoveObjects.clear();
    }
}

void Scene::gameObjectDraw()
{
    std::stable_sort(_gameObjects.begin(), _gameObjects.end(),Scene::compareDrawLayerOrder);
    
    for(auto& object : _gameObjects)
    {
        object->draw();
    }
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
    gameObject->setScene(getThis<Scene>());
    _gameObjects.push_back(gameObject);
}

void Scene::onScreenTouched(TouchInfo& touchInfo)
{
    for(auto& object : _gameObjects)
    {
        object->onScreenTouched(touchInfo);
    }
}

bool Scene::findGameObject(const std::shared_ptr<GameObject>& obj)
{
    for(auto ptr : _gameObjects)
    {
        if(obj == ptr)
            return true;
    }
    
    return false;
}

void Scene::removeGameObject(const std::shared_ptr<GameObject>& obj)
{
    if(findGameObject(obj))
        _waitRemoveObjects.push_back(obj);
}

bool Scene::compareDrawLayerOrder(std::shared_ptr<GameObject> left, std::shared_ptr<GameObject> right)
{
    return left->getDrawLayer() < right->getDrawLayer();
}
