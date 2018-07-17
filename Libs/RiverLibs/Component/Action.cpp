//
//  Action.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/05.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Action.hpp"

RotateBy::RotateBy(const std::shared_ptr<GameObject>& gameObjectPtr,const Vector3 axis,const float rad,const float time,const Lerp::rate lerpRate):
ActionObj(gameObjectPtr),
_axis(axis),
_rad(rad),
_time(time),
_timeCount(0.0f),
_lerpRate(lerpRate)
{
    
}

void RotateBy::update()
{
    if(_isArrived)
        return;

    float delta = Application::getInstance()->getDeltaTime();
    _timeCount += delta;

    float lerpRad = Lerp::CalculateLerp(0.0f, _rad, 0.0f, _time, _timeCount, _lerpRate);
    Quaternion qt = _startQuat * Quaternion(_axis, lerpRad);

    _gameObject.lock()->getTransform()->setRotation(qt);

    if(_timeCount > _time)
    {
        _timeCount = 0.0f;
        _isArrived = true;
        _gameObject.lock()->getTransform()->setRotation(_startQuat * Quaternion(_axis,_rad));
    }
}

void RotateBy::run()
{
    _startQuat = _gameObject.lock()->getTransform()->getRotation();
}

MoveTo::MoveTo(const std::shared_ptr<GameObject>& gameObjectPtr,const Vector3 endPos, const float time,Lerp::rate lerpRate):
ActionObj(gameObjectPtr),
_endPos(endPos),
_time(time),
_lerpRate(lerpRate)
{
    
}

void MoveTo::update()
{
    if(_isArrived)
        return;
    
    float delta = Application::getInstance()->getDeltaTime();
    _timeCount += delta;
    
    Vector3 lerpPos = Lerp::CalculateLerp(_startPos, _endPos, 0.0f, _time, _timeCount, _lerpRate);
    _gameObject.lock()->getTransform()->setPosition(lerpPos);
    
    if(_timeCount > _time)
    {
        _timeCount = 0.0f;
        _isArrived = true;
        _gameObject.lock()->getTransform()->setPosition(_endPos);
    }
}

void MoveTo::run()
{
    _startPos = _gameObject.lock()->getTransform()->getPosition();
}

Action::Action(const std::shared_ptr<GameObject>& gameObjectPtr):
Component(gameObjectPtr)
{
    
}

void Action::update()
{
    if(_actions.size() <= 0)
        return;
    
    if(_isRun)
    {
        _actions[_index]->update();
        if(_actions[_index]->getIsArrived())
        {
            _index++;
            if(_index >= _actions.size())
            {
                _index = 0;
                _isRun = false;
                return;
            }
            _actions[_index]->run();
        }
    }
}

void Action::addRotateBy(const float time, const Vector3 axis, const float rad,const Lerp::rate lerpRate)
{
    auto rotateBy = ObjectFactory::create<RotateBy>(_gameObject.lock(),axis,rad,time,lerpRate);
    _actions.push_back(rotateBy);
}

void Action::addMoveTo(const float time, const Vector3 endPos,const Lerp::rate lerpRate)
{
    auto moveTo = ObjectFactory::create<MoveTo>(_gameObject.lock(),endPos,time,lerpRate);
    _actions.push_back(moveTo);
}

void Action::run()
{
    if(_actions.size() == 0)
        return;
    
    _actions[0]->run();
    _isRun = true;
}

void Action::stop()
{
    _isRun = false;
    _index = 0;
}

void Action::actionClear()
{
    _actions.clear();
}
