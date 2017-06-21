//
//  Sprite.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "river.h"
#include "HelloWorldScene.hpp"

Sprite::Sprite()
{
    
}

Sprite::~Sprite()
{
    
}

std::shared_ptr<Sprite> Sprite::create()
{
    auto ret = std::shared_ptr<Sprite>(new Sprite());
    
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
    
    auto transPtr = getTransform();
    transPtr->setPosition(Vector3(50,100,0));
    
    auto app = Application::getInstance();
    _useProgram = app->getProgram();
    
    _attr_pos = _useProgram->getAttribLocation("attr_pos");
    assert(_attr_pos >= 0);
    _unif_matrix = _useProgram->getUnifLocation("unif_matrix");
    assert(_unif_matrix >= 0);
    
    return true;
}

void Sprite::update()
{
    auto transPtr = getTransform();
    Vector3 add = Vector3(100,100,0) * Application::getInstance()->getDeltaTime();
    transPtr->setPosition(transPtr->getPosition() + add);
    
}

void Sprite::draw()
{
    _useProgram->use();
    glEnableVertexAttribArray(_attr_pos);
    
    const GLfloat position[] = {
        -0.5f,0.5f,
        -0.5f,-0.5f,
        0.5f,0.5f,
        0.5f,-0.5f
    };
    
    glVertexAttribPointer(_attr_pos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
    
    auto app = Application::getInstance();
    
    auto pos = getTransform()->getPosition();
    
    const GLfloat xScale = (GLfloat)_spriteWidth / (GLfloat) app->getSurfaceWidth() * 2.0f;
    const GLfloat yScale = (GLfloat)_spriteHeight / (GLfloat) app->getSurfaceHeight() * 2.0f;
    
    const Matrix4x4 scale = Matrix4x4::createScale(xScale, yScale, 0);
    
    const GLfloat vertexLeft = 0.5f + (1.0 - xScale) * 0.5f;
    const GLfloat vertexTop = 0.5f + (1.0f - yScale) * 0.5f;
    const GLfloat moveX = (GLfloat)pos.x / (GLfloat) app->getSurfaceWidth() * 2.0f;
    const GLfloat moveY = -((GLfloat)pos.y / (GLfloat) app->getSurfaceHeight() * 2.0f);
    
    const Matrix4x4 translate = Matrix4x4::createTranslate(-vertexLeft+moveX, vertexTop + moveY, 0);
    
    Matrix4x4 matrix = Matrix4x4::multiply(translate, scale);
    
    glUniformMatrix4fv(_unif_matrix, 1, GL_FALSE, matrix.matrix);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
