//
//  Scene.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <memory>
#include "Helper.hpp"

class GameObject;

class Scene : public ObjectInterface
{
protected:
    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    
public:
    Scene();
    virtual ~Scene();
    
    static std::shared_ptr<Scene> create();
    
    virtual bool init();
    
    virtual void update(){}
    
    virtual void draw();
    
    virtual void addGameObject(std::shared_ptr<GameObject> gameObject);
};

#endif /* Scene_hpp */
