//
//  GameObject.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <new>
#include <memory>

class GameObject : public ObjectInterface,public ShapeInterface
{
public:
    GameObject();
    
    virtual ~GameObject();

    static std::shared_ptr<GameObject> create();
    
    virtual bool init(){ return true;};
    
    virtual void update(){};
    
    virtual void draw(){};
};



#endif /* GameObject_hpp */
