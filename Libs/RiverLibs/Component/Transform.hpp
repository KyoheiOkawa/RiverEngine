//
//  Transform.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/19.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include "stdinc.h"
#include "Component.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

class Transform : public Component
{
protected:
    Vector3 _scale;
    Vector3 _position;
    Quaternion _rotation;
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
    
    void translate(Vector3 moveVec)
    {
        _position += moveVec;
    }
    
    void rotate(Vector3 axis,float angleRad);
    
    void setRotation(Quaternion rotation)
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
    
    Quaternion getRotation()
    {
        return _rotation;
    }
    
    Vector3 getPivot()
    {
        return _pivot;
    }
};

#endif /* Transform_hpp */
