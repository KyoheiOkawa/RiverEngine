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

class GameObject;

class Scene{
protected:
    Scene();
    virtual ~Scene();
    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    
public:
    static Scene* create();
    
    virtual bool init();
    
    virtual void update(){}
    
    virtual void draw();
    
    virtual void addGameObject(std::shared_ptr<GameObject> gameObject){
        _gameObjects.push_back(gameObject);
    }
};

#endif /* Scene_hpp */
