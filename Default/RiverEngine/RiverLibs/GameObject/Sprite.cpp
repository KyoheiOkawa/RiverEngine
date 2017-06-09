//
//  Sprite.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "river.h"

Sprite::Sprite()
{
    
}

Sprite::~Sprite()
{
    
}

Sprite* Sprite::create()
{
    auto ret = new (std::nothrow) Sprite();
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool Sprite::init()
{
    if(!GameObject::init())
        return false;
    
    return true;
}

void Sprite::update()
{
    pixel_x += 1;
    pixel_y += 1;
}

void Sprite::draw()
{
    _useProgram->use();
    glEnableVertexAttribArray(0);
    
    auto width = Application::getInstance()->getSurfaceWidth();
    auto height = Application::getInstance()->getSurfaceHeight();
    
    GLfloat VERTEX_LEFT = ((GLfloat)pixel_x / (GLfloat)width) * 2.0f - 1.0f;
    GLfloat VERTEX_RIGHT = ((GLfloat)(pixel_x + pixel_width) / (GLfloat)width) * 2.0f - 1.0f;
    GLfloat VERTEX_TOP = (((GLfloat)pixel_y / (GLfloat) height) * 2.0f - 1.0f) * -1.0f;
    GLfloat VERTEX_BOTTOM = (((GLfloat)(pixel_y + pixel_height) / (GLfloat) height) * 2.0f - 1.0f) * -1.0f;
    
    const GLfloat position[] = {
        VERTEX_LEFT,VERTEX_TOP,
        VERTEX_LEFT,VERTEX_BOTTOM,
        VERTEX_RIGHT,VERTEX_TOP,
        VERTEX_RIGHT,VERTEX_BOTTOM
    };
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
