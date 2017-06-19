//
//  Component.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/11.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>

class GameObject;

class Component : public ObjectInterface,public ShapeInterface
{
protected:
    std::weak_ptr<GameObject> _gameObject;
    
    Component(const std::shared_ptr<GameObject>& GameObjectPtr);
    
    virtual ~Component();
public:    
    virtual bool init() override{return true;};
    virtual void update() override{};
    virtual void draw() override{};
    
    void attachGameObject(const std::shared_ptr<GameObject>& gameObjectPtr){
        _gameObject = gameObjectPtr;
    }
};

#endif /* Component_hpp */
