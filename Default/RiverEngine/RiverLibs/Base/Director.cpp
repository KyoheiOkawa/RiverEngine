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

bool Director::registerTexture(std::string texKey, std::string fileName)
{
    if(!isRegisteredTexture(texKey))
    {
        GLuint id;
        glGenTextures(1, &id);
        assert(id != 0);
        assert(glGetError() == GL_NO_ERROR);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        glBindTexture(GL_TEXTURE_2D, id);
        assert(glGetError() == GL_NO_ERROR);
        
        RawPixelImage *image = RawPixelImage_load(fileName.c_str(), TEXTURE_RAW_RGBA8);
        assert(image != NULL);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixel_data);
        assert(glGetError() == GL_NO_ERROR);
        
        RawPixelImage_free(image);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        assert(glGetError() == GL_NO_ERROR);
        
        _textureCache[texKey] = id;
        
        return true;
    }
    
    return false;
}

bool Director::unregisterTexture(std::string texKey)
{
    if(isRegisteredTexture(texKey)){
        
        glDeleteTextures(1, &_textureCache[texKey]);
        _textureCache.erase(texKey);
        
        return true;
    }
    
    return false;
}

bool Director::isRegisteredTexture(std::string texKey)
{
    auto it = _textureCache.find(texKey);
    if(it != _textureCache.end())
        return true;
    
    return false;
}

GLuint Director::getRegesterdTextureId(std::string texKey)
{
    if(isRegisteredTexture(texKey)){
        return _textureCache[texKey];
    }
    
    return 0;
}
