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
    
//    auto fileUtils = FileUtils::getInstance();
//    
//    std::string vstr = fileUtils->getStringFromFile("Shaders/SimpleShader", "vsh").c_str();
//    std::string fstr = fileUtils->getStringFromFile("Shaders/SimpleShader", "fsh").c_str();
//    
//    GLchar *vertex_shader_source = new GLchar[vstr.size() + 1];
//    
//    GLchar *fragment_shader_source = new GLchar[fstr.size() + 1];
//    
//    std::strcpy(vertex_shader_source, vstr.c_str());
//    std::strcpy(fragment_shader_source, fstr.c_str());
//    
//    _program = GLProgram::createWithByteArray(vertex_shader_source, fragment_shader_source);
//    
//    delete[] vertex_shader_source;
//    delete[] fragment_shader_source;
    
    _program = GLProgram::createWithFile("Shaders/SimpleShader", "Shaders/SimpleShader");
    
    _program->use();
    
    static GLfloat position[] = {
        0.0f,1.0f,
        1.0f,-1.0f,
        -1.0f,-1.0f
    };
    
    _position = position;
    
    return true;
}

void HelloWorldScene::update()
{
    
}

void HelloWorldScene::draw()
{
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)_position);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
