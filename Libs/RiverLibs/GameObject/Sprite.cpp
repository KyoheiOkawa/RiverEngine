//
//  Sprite.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "stdinc.h"
#include "river.h"

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

std::shared_ptr<Sprite> Sprite::createWithTexture(std::string texPath)
{
    auto ret = std::shared_ptr<Sprite>(new Sprite);
    
    if(ret && ret->init())
    {
        auto director = Director::getInstance();

        if(!director->isRegisteredTexture(texPath))
            director->registerTexture(texPath, texPath);
        
        auto texInfo = director->getRegesterdTextureInfo(texPath);
        
        ret->_spriteSize.x = texInfo->width;
        ret->_spriteSize.y = texInfo->height;
        ret->_texture_id = texInfo->id;
        
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
    
    auto director = Director::getInstance();
    _useProgram = director->getGLProgram("PTSprite");
    
    _attr_pos = _useProgram->getAttribLocation("attr_pos");
    _attr_uv = _useProgram->getAttribLocation("attr_uv");
    _unif_matrix = _useProgram->getUnifLocation("unif_matrix");
    _unif_texture = _useProgram->getUnifLocation("unif_texture");
    
    return true;
}

void Sprite::update()
{
    auto transPtr = getTransform();
    float delta = Application::getInstance()->getDeltaTime();
    Vector3 add = Vector3(100,100,0) * delta;
    transPtr->setPosition(transPtr->getPosition() + add);
    transPtr->setRotation(transPtr->getRotation() + Vector3(0,0,45) * delta);
    
}

void Sprite::draw()
{
    _useProgram->use();
    glEnableVertexAttribArray(_attr_pos);
    glEnableVertexAttribArray(_attr_uv);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    const PositionTexture vertex[] ={
        {{-0.5f,0.5f},{0,0}},
        {{-0.5f,-0.5f},{0,1}},
        {{0.5f,0.5f},{1,0}},
        {{0.5f,-0.5f},{1,1}}
    };
    
    glVertexAttribPointer(_attr_pos, 2, GL_FLOAT, GL_FALSE, sizeof(PositionTexture), (GLvoid*)vertex);
    glVertexAttribPointer(_attr_uv, 2, GL_FLOAT, GL_FALSE, sizeof(PositionTexture), (GLvoid*)((GLubyte*)vertex + sizeof(GLfloat)*3));
    
    auto app = Application::getInstance();
    
    auto trans = getTransform();
    auto pos = trans->getPosition();
    auto scale = trans->getScale();
    auto rotation = trans->getRotation();
    
    Vector3 pivot = trans->getPivot();
    
    Matrix4x4 matrix = Matrix4x4::create2DAffine(pos, _spriteSize , scale, rotation.z, Vector2(app->getSurfaceWidth(),app->getSurfaceHeight()), pivot);
    
    glUniformMatrix4fv(_unif_matrix, 1, GL_FALSE, matrix.matrix);
    glUniform1i(_unif_texture, 0);
    
    glBindTexture(GL_TEXTURE_2D, _texture_id);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Sprite::setTexture(std::string texKey)
{
    auto director = Director::getInstance();
    
    auto texInfo = director->getRegesterdTextureInfo(texKey);
    
    _texture_id = texInfo->id;
    
    _spriteSize.x = texInfo->width;
    _spriteSize.y = texInfo->height;
}

void Sprite::onScreenTouched(TouchInfo& touchInfo)
{
    if(touchInfo.type == TouchType::BEGAN)
    {
        auto transPtr = getTransform();
        transPtr->setPosition(Vector3(touchInfo.posX,touchInfo.posY,0));
    }
}
