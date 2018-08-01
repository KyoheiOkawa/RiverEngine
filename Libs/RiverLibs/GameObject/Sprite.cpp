//
//  Sprite.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "stdinc.h"
#include "river.h"

Sprite::Sprite():
_is3DWorld(false)
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
    
    std::vector<PositionTexture> vertex ={
        {{-0.5f,0.5f},{0,0}},
        {{-0.5f,-0.5f},{0,1}},
        {{0.5f,0.5f},{1,0}},
        {{0.5f,-0.5f},{1,1}}
    };
    
    _meshResource = MeshResource<PositionTexture>::createWithVertex(vertex);
    
    return true;
}

void Sprite::update()
{

}

void Sprite::draw()
{
    _useProgram->use();
    glEnableVertexAttribArray(_attr_pos);
    glEnableVertexAttribArray(_attr_uv);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glVertexAttribPointer(_attr_pos, 2, GL_FLOAT, GL_FALSE, sizeof(PositionTexture), (GLvoid*)_meshResource->GetVertexPointer());
    glVertexAttribPointer(_attr_uv, 2, GL_FLOAT, GL_FALSE, sizeof(PositionTexture), (GLvoid*)((GLubyte*)_meshResource->GetVertexPointer() + sizeof(GLfloat)*3));
    
    auto app = Application::getInstance();
    
    auto trans = getTransform();
    auto pos = trans->getPosition();
    auto scale = trans->getScale();
    auto rotation = trans->getRotation();
    
    Vector3 pivot = trans->getPivot();
    
    Matrix4x4 matrix;
    
    if(!_is3DWorld)
    {
        matrix = Matrix4x4::create2DAffine(pos, _spriteSize , scale, rotation.z, Vector2(app->getSurfaceWidth(),app->getSurfaceHeight()), pivot);
    }
    else
    {
        Matrix4x4 lookAt,projection;
        Director::getInstance()->getScene()->GetMainCamera()->GetLookAtProjection(lookAt, projection);
        
        Matrix4x4 pos,scale,rot;
        auto trans = getTransform();
        pos = Matrix4x4::createTranslate(trans->getPosition().x, trans->getPosition().y, trans->getPosition().z);
        scale = Matrix4x4::createScale(trans->getScale().x, trans->getScale().y, trans->getScale().z);
        rot = Matrix4x4::createRotate(trans->getRotation());
        matrix = projection * lookAt * pos * scale * rot;
    }
    
    glUniformMatrix4fv(_unif_matrix, 1, GL_FALSE, matrix.matrix);
    glUniform1i(_unif_texture, 0);
    
    glBindTexture(GL_TEXTURE_2D, _texture_id);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(_attr_pos);
    glDisableVertexAttribArray(_attr_uv);
}

void Sprite::setTexture(std::string texKey)
{
    auto director = Director::getInstance();
    
    auto texInfo = director->getRegesterdTextureInfo(texKey);
    
    _texture_id = texInfo->id;
    
    _spriteSize.x = texInfo->width;
    _spriteSize.y = texInfo->height;
}
