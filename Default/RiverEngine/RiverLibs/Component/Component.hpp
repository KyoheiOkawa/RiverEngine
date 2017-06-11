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
#include "river.h"

class Component
{
protected:
    std::weak_ptr<GameObject> _gameObject;
    
    Component(const std::shared_ptr<GameObject>& GameObjectPtr);
    
    ~Component(){};
public:
    
};

#endif /* Component_hpp */
