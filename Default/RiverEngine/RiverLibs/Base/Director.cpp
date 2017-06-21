//
//  Director.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "river.h"

Director* Director::_director = nullptr;

Director* Director::getInstance()
{
    
    if(_director == nullptr){
        _director = new Director();
        _director->createDefaultGLPrograms();
    }
    
    return _director;
}

void Director::updateScene()
{
    _scene->update();
    _scene->gameObjectUpdate();
}

void Director::drawScene()
{
    _scene->draw();
    _scene->gameObjectDraw();
}

void Director::createDefaultGLPrograms()
{
    _programMap["SpriteShader"] = GLProgram::createWithFile("Shaders/SimpleShader", "Shaders/SimpleShader");
}

GLProgram* Director::getGLProgram(std::string name)
{
    auto ret = _programMap[name];
    //シェーダーが見つかりません
    assert(ret);
    
    return ret;
}

void Director::addGLProgram(GLProgram* program,std::string name)
{
    auto check = _programMap[name];
    //すでに同じ名前のプログラムが追加されています
    assert(!check);
    
    _programMap[name] = program;
}
