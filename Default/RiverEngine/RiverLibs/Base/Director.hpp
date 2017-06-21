//
//  Director.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Director_hpp
#define Director_hpp

#include <stdio.h>
#include <memory.h>

class Scene;

class Director{
private:
    Director(){}
    static Director* _director;
    std::shared_ptr<Scene> _scene;
public:
    static Director* getInstance();
    void updateScene();
    void drawScene();
    void setScene(std::shared_ptr<Scene> scene){
        _scene = scene;
    }
    std::shared_ptr<Scene> getScene(){
        return _scene;
    }
};

#endif /* Director_hpp */
