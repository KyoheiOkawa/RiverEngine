//
//  Confetti.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/25.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Confetti.hpp"

ConfettiFragment::ConfettiFragment(const InitParam initParam):
_initParam(initParam)
{
    
}

shared_ptr<ConfettiFragment> ConfettiFragment::create(const ConfettiFragment::InitParam initParam)
{
    shared_ptr<ConfettiFragment> ret(new ConfettiFragment(initParam));
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool ConfettiFragment::init()
{
    GameObject::init();
    
    auto trans = getTransform();
    trans->setPosition(_initParam._startPos);
    trans->setScale(Vector3(_initParam._scale,_initParam._scale,_initParam._scale));
    
    _useProgram = Director::getInstance()->getGLProgram("PSprite");
    
    _attr_pos = _useProgram->getAttribLocation("attr_pos");
    _unif_color = _useProgram->getUnifLocation("unif_color");
    _unif_matrix = _useProgram->getUnifLocation("unif_matrix");
    
    
    vector<Position> vertices={
        {{-0.5f,0.5f}},
        {{-0.5f,-0.5f}},
        {{0.5f,0.5f}},
        {{0.5f,-0.5f}}
    };
    
    _meshResource = MeshResource<Position>::createWithVertex(vertices);
    
    return true;
}

void ConfettiFragment::update()
{
    auto delta = Application::getInstance()->getDeltaTime();
    
    auto trans = getTransform();
    Vector3 pos = trans->getPosition();
    Vector3 scale = trans->getScale();
    Quaternion rot = trans->getRotation();
    
    pos.x += _initParam._force.x * delta;
    pos.y += _initParam._fallSpeed * delta;
    
    scale.x -= _initParam._smallSpeed * delta;
    if(scale.x < 0.0f) scale.x = 0.0f;
    scale.y -= _initParam._smallSpeed * delta;
    if(scale.y < 0.0f) scale.y = 0.0f;
    
    rot.z += _initParam._angularVelocity;
    
    trans->setPosition(pos);
    trans->setScale(scale);
    trans->setRotation(rot);
}

void ConfettiFragment::draw()
{
    _useProgram->use();
    glEnableVertexAttribArray(_attr_pos);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glVertexAttribPointer(_attr_pos, 3, GL_FLOAT, GL_FALSE, sizeof(Position), (GLvoid*)_meshResource->GetVertexPointer());
    
    auto app = Application::getInstance();
    
    auto trans = getTransform();
    auto pos = trans->getPosition();
    auto scale = trans->getScale();
    auto rotation = trans->getRotation();
    
    Vector3 pivot = trans->getPivot();
    
    Matrix4x4 matrix = Matrix4x4::create2DAffine(pos, Vector2(1,1) , scale, rotation.z, Vector2(app->getSurfaceWidth(),app->getSurfaceHeight()), pivot);
    
    glUniformMatrix4fv(_unif_matrix, 1, GL_FALSE, matrix.matrix);
    glUniform4f(_unif_color, _initParam._color.r, _initParam._color.g, _initParam._color.b, _initParam._color.a);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(_attr_pos);
}
