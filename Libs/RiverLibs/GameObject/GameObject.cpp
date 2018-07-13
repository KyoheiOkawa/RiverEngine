//
//  GameObject.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "stdinc.h"
#include "river.h"

GameObject::GameObject()
{
    
}

GameObject::~GameObject()
{
    
}

bool GameObject::init()
{
    setTransform(ObjectFactory::create<Transform>(getThis<GameObject>()));
    
    return true;
}

std::shared_ptr<Component> GameObject::searchComponent(std::type_index typeId)const
{
    auto it = _compMap.find(typeId);
    if(it != _compMap.end()){
        return it->second;
    }
    
    return nullptr;
}

void GameObject::addMakedComponent(std::type_index typeId, const std::shared_ptr<Component>& ptr)
{
    if(!searchComponent(typeId)){
        _compOrder.push_back(typeId);
    }
    
    _compMap[typeId] = ptr;
    ptr->attachGameObject(getThis<GameObject>());
}

void GameObject::setTransform(const std::shared_ptr<Transform>& ptr){
    ptr->attachGameObject(getThis<GameObject>());
    _transform = ptr;
}

std::shared_ptr<GameObject> GameObject::create()
{
    auto ret = std::shared_ptr<GameObject>(new GameObject());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

void GameObject::componentUpdate()
{
    for(auto& comp : _compMap)
        comp.second->update();
}

void GameObject::componentDraw()
{
    for(auto& comp : _compMap)
        comp.second->draw();
}

void GameObject::addTag(std::string tag)
{
    _tags.insert(tag);
}

bool GameObject::findTag(std::string tag)
{
    auto itr = std::find_if(_tags.begin(), _tags.end(), [tag](string str){
                return str == tag;
            });

    if(itr != _tags.end())
        return true;
    
    return false;
}
