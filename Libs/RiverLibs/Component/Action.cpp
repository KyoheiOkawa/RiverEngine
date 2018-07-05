//
//  Action.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/05.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Action.hpp"

RotateBy::RotateBy(const std::shared_ptr<GameObject>& gameObjectPtr,const Vector3 axis,const float rad,const float time):
ActionObj(gameObjectPtr),
_axis(axis),
_rad(rad),
_time(time),
_timeCount(0.0f)
{
    
}

void RotateBy::update()
{
    if(_isArrived)
        return;

    float delta = Application::getInstance()->getDeltaTime();
    _timeCount += delta;

    float lerpRad = Lerp::CalculateLerp(0.0f, _rad, 0.0f, _time, _timeCount, Lerp::Linear);
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

void Action::addRotateBy(const float time, const Vector3 axis, const float rad)
{
    auto rotateBy = ObjectFactory::create<RotateBy>(_gameObject.lock(),axis,rad,time);
    _actions.push_back(rotateBy);
}

void Action::run()
{
    _isRun = true;
}

void Action::actionClear()
{
    _actions.clear();
}
