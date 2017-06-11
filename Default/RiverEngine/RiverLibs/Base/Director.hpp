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

class Scene;

class Director{
private:
    Director(){}
    static Director* _director;
    Scene* _scene;
public:
    static Director* getInstance();
    void updateScene();
    void drawScene();
    void setScene(Scene* scene){
        _scene = scene;
    }
    Scene* getScene(){
        return _scene;
    }
};

#endif /* Director_hpp */
