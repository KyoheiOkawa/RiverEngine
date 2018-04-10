//
//  HelloWorldScene.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef HelloWorldScene_hpp
#define HelloWorldScene_hpp

#include <stdio.h>
#include "river.h"

class HelloWorldScene : public Scene
{
public:
    HelloWorldScene();
    virtual ~HelloWorldScene();
    
    static std::shared_ptr<Scene> createScene();
    
    virtual bool init();
    
    virtual void update();
    
    virtual void draw();
    
    virtual void onScreenTouched(TouchInfo& touchInfo)override;
};


#endif /* HelloWorldScene_hpp */
