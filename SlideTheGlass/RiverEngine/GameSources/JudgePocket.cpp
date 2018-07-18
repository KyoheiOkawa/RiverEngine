//
//  JudgePocket.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/13.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "JudgePocket.hpp"
#include "MainScene.hpp"

JudgePocket::JudgePocket():
_defaultRadius(0.3f),
_hightScoreRadius(0.05f),
_radius(_defaultRadius),
_minRadius(0.08f),
_defaultColor(Color4(0.2f,0.8f,0.2f,0.5f)),
_color(_defaultColor),
_highScoreColor(Color4(0.94f,0.98f,0.13f,0.5f)),
_onColor(Color4(0.8f,0.2,0.2f,0.5f)),
_glassRadius(0.05f),
_randomMoveSpeedSec(0.3f)
{
    
}

std::shared_ptr<JudgePocket> JudgePocket::create()
{
    shared_ptr<JudgePocket> ret(new JudgePocket());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool JudgePocket::init()
{
    GameObject::init();
    
    auto trans = getTransform();
    trans->setPosition(Vector3(0.1f,0.8f,0.0f));
    
    auto action = addComponent<Action>();
    
    addTag("JudgePocket");
    
    moveRandom();
    
    return true;
}

void JudgePocket::update()
{
    updateCircleColor();
}

void JudgePocket::draw()
{
    auto trans = getTransform();
    PrimitiveDraws::drawPlaneCircle(trans->getPosition(), _radius, _color);
    
    auto scene = getDynamicScene<MainScene>();
    if(scene->getScore() % 5 == 0 && scene->getScore() != 0)
        PrimitiveDraws::drawPlaneCircle(trans->getPosition()+Vector3(0,0.005f,0.0f), _hightScoreRadius, _highScoreColor);
}

void JudgePocket::updateCircleColor()
{
    if(!_glass.lock())
    {
        _glass = getScene()->findGameObject("Glass");
        if(!_glass.lock())
            return;
    }
    
    auto glassLock = _glass.lock();
    if(isInPocket(glassLock->getTransform()->getPosition()))
        _color = _onColor;
    else
        _color = _defaultColor;
}

void JudgePocket::moveRandom()
{
    _radius -= 0.002f;
    if(_radius < _minRadius)
        _radius = _minRadius;
    
    auto trans = getTransform();
    Vector3 setPos = trans->getPosition();
    
    setPos.x = Random::getInstance()->range(-0.5f+_radius, 0.5f-_radius);
    setPos.z = Random::getInstance()->range(-1.1f+_radius*2, 0.0f+_radius);
    
    auto action = getComponent<Action>();
    action->stop();
    action->actionClear();
    
    action->addMoveTo(_randomMoveSpeedSec, setPos);
    action->run();
}

bool JudgePocket::isInPocket(Vector3 pos)
{
    Vector3 nowPos = getTransform()->getPosition();
    float length = (nowPos - pos).magnitude();
    if(length <= _radius + _glassRadius)
    {
        return true;
    }
    
    return false;
}

bool JudgePocket::isInHighScorePocket(Vector3 pos)
{
    auto scene = getDynamicScene<MainScene>();
    if(scene->getScore() % 5 != 0 || scene->getScore() == 0)
        return false;
    
    Vector3 nowPos = getTransform()->getPosition();
    float length = (nowPos - pos).magnitude();
    if(length <= _hightScoreRadius + _glassRadius)
    {
        return true;
    }
    
    return false;
}

void JudgePocket::reset()
{
    _radius = _defaultRadius;
}
