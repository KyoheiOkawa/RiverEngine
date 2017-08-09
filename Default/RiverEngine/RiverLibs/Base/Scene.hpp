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
#include <vector>
#include "Helper.hpp"

class GameObject;

class Scene : public ObjectInterface
{
protected:
    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    std::vector<std::shared_ptr<GameObject>> _waitRemoveObjects;
    
public:
    Scene();
    virtual ~Scene();
    
    static std::shared_ptr<Scene> create();
    
    virtual bool init();
    
    virtual void update(){}
    
    virtual void draw();
    
    void gameObjectUpdate();
    
    void gameObjectDraw();
    
    void addGameObject(std::shared_ptr<GameObject> gameObject);
    
    bool findGameObject(const std::shared_ptr<GameObject>& obj);
    
    void removeGameObject(const std::shared_ptr<GameObject>& gameObject);
    
    void onScreenTouched(TouchInfo& touchInfo);
    
private:
    
    static bool compareDrawLayerOrder(std::shared_ptr<GameObject> left,std::shared_ptr<GameObject> right);
};

#endif /* Scene_hpp */
