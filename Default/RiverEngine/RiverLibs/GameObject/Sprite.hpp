//
//  Sprite.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include "GLProgram.hpp"

class Sprite : public GameObject
{
protected:
    Sprite();
    virtual ~Sprite();
    
    int pixel_x = 50;
    int pixel_y = 100;
    int pixel_width = 200;
    int pixel_height = 300;
    
    GLProgram* _useProgram;
    
public:
    virtual void setUseProgram(GLProgram* program){
        _useProgram = program;
    }
    
    static Sprite* create();
    
    virtual bool init();
    
    virtual void update();
    
    virtual void draw();
};

#endif /* Sprite_hpp */
