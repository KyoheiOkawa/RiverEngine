//
//  HelloWorldScene.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "HelloWorldScene.hpp"

HelloWorldScene::HelloWorldScene()
{
    
}

HelloWorldScene::~HelloWorldScene()
{
    
}

HelloWorldScene* HelloWorldScene::createScene()
{
    auto ret = new (std::nothrow) HelloWorldScene();
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool HelloWorldScene::init()
{
    if(!Scene::init())
        return false;
    
    _program = GLProgram::createWithFile("Shaders/SimpleShader", "Shaders/SimpleShader");
    
    _program->use();
    
    static GLfloat position[] = {
        0.0f,1.0f,
        1.0f,-1.0f,
        -1.0f,-1.0f
    };
    
    _position = position;
    
    auto sprite = Sprite::create();
    this->addGameObject(sprite);
    sprite->setUseProgram(_program);
    
    return true;
}

void HelloWorldScene::update()
{
    
}

void HelloWorldScene::draw()
{
//    glEnableVertexAttribArray(0);
//    
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)_position);
//    
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    Scene::draw();
}
