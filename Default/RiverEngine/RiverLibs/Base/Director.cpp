//
//  Director.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "river.h"

Director* Director::_director = nullptr;

Director* Director::getInstance()
{
    
    if(_director == nullptr){
        _director = new Director();
    }
    
    return _director;
}

void Director::updateScene()
{
    _scene->update();
}

void Director::drawScene()
{
    _scene->draw();
}
