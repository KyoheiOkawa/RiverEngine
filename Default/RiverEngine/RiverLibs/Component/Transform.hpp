//
//  Transform.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/19.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include <memory>
#include "Vector3.hpp"

class Transform : public Component
{
protected:
    Vector3 _scale;
    Vector3 _position;
public:
    explicit Transform(const std::shared_ptr<GameObject>& gameObjectPtr);
    
    virtual ~Transform();
    
    void setScale(Vector3 scale){
        _scale = scale;
    }
    
    void setPosition(Vector3 position){
        _position = position;
    }
    
    Vector3 getScale(){
        return _scale;
    }
    
    Vector3 getPosition(){
        return _position;
    }
};

#endif /* Transform_hpp */
