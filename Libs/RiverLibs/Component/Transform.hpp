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
    Vector3 _rotation;
    Vector3 _pivot;
public:
    explicit Transform(const std::shared_ptr<GameObject>& gameObjectPtr);
    
    virtual ~Transform();
    
    void setScale(Vector3 scale)
    {
        _scale = scale;
    }
    
    void setPosition(Vector3 position)
    {
        _position = position;
    }
    
    void setRotation(Vector3 rotation)
    {
        _rotation = rotation;
    }
    
    void setPivot(Vector3 pivot)
    {
        _pivot = pivot;
    }
    
    Vector3 getScale()
    {
        return _scale;
    }
    
    Vector3 getPosition()
    {
        return _position;
    }
    
    Vector3 getRotation()
    {
        return _rotation;
    }
    
    Vector3 getPivot()
    {
        return _pivot;
    }
};

#endif /* Transform_hpp */
