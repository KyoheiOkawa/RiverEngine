//
//  JudgePocket.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/13.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "JudgePocket.hpp"

JudgePocket::JudgePocket():
_defaultRadius(0.3f),
_hightScoreRadius(0.05f),
_radius(_defaultRadius),
_defaultColor(Color4(0.2f,0.8f,0.2f,0.5f)),
_color(_defaultColor),
_highScoreColor(Color4(0.94f,0.98f,0.13f,0.5f)),
_onColor(Color4(0.8f,0.2,0.2f,0.5f)),
_glassRadius(0.05f)
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
    action->addMoveTo(3.0f, Vector3(0,0.8f,0.75f));
    action->run();
    
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
    Vector3 nowPos = getTransform()->getPosition();
    float length = (nowPos - pos).magnitude();
    if(length <= _hightScoreRadius + _glassRadius)
    {
        return true;
    }
    
    return false;
}
