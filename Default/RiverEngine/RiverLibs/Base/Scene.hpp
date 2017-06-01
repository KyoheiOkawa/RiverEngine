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

class Scene{
protected:
    Scene();
    virtual ~Scene();
public:
    static Scene* create();
    
    virtual bool init();
    
    virtual void update(){}
    
    virtual void draw(){}
};

#endif /* Scene_hpp */
