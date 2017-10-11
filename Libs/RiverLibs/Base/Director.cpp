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
    _programMap["PTSprite"] = GLProgram::createWithFile("Shaders/PTSprite", "Shaders/PTSprite");
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
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        assert(glGetError() == GL_NO_ERROR);
        
        bool isPod = Texture2D_checkPowerOfTwoWH(image->width, image->height);
        if(!isPod){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        
        std::shared_ptr<TextureInfo> texInfo(new TextureInfo);
        texInfo->id = id;
        texInfo->width = image->width;
        texInfo->height = image->height;
        texInfo->isPod = isPod;
        
        RawPixelImage_free(image);
        
        _textureCache[texKey] = texInfo;
        
        return true;
    }
    
    return false;
}

bool Director::unregisterTexture(std::string texKey)
{
    if(isRegisteredTexture(texKey)){
        
        glDeleteTextures(1, &_textureCache[texKey]->id);
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

std::shared_ptr<TextureInfo> Director::getRegesterdTextureInfo(std::string texKey)
{
    if(isRegisteredTexture(texKey)){
        return _textureCache[texKey];
    }
    
    return 0;
}

void Director::onScreenTouched(TouchInfo& touchInfo)
{
    _scene->onScreenTouched(touchInfo);
}
