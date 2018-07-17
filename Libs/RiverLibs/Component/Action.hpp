//
//  Action.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/05.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Action_hpp
#define Action_hpp

#include "river.h"

class ActionObj : public Component
{
protected:
    bool _isArrived = false;
public:
    ActionObj(const std::shared_ptr<GameObject>& gameObjectPtr):
    Component(gameObjectPtr)
    {}
    virtual ~ActionObj(){}
    
    virtual void update() override{};
    virtual void run(){};
    
    bool getIsArrived(){return _isArrived;}
};

class RotateBy : public ActionObj
{
    float _time;
    float _timeCount;
    Vector3 _axis;
    float _rad;
    Quaternion _startQuat;
    Lerp::rate _lerpRate;
public:
    RotateBy(const std::shared_ptr<GameObject>& gameObjectPtr,const Vector3 axis,const float rad,const float time,const Lerp::rate lerpRate = Lerp::rate::Linear);
    virtual ~RotateBy(){}
    
    virtual void update() override;
    virtual void run() override;
};

class MoveTo : public ActionObj
{
    float _time;
    float _timeCount;
    Vector3 _startPos;
    Vector3 _endPos;
    Lerp::rate _lerpRate;
public:
    MoveTo(const std::shared_ptr<GameObject>& gameObjectPtr,const Vector3 endPos, const float time,Lerp::rate lerpRate = Lerp::rate::Linear);
    virtual ~MoveTo(){}
    
    virtual void update() override;
    virtual void run() override;
};

class Action : public Component
{
    vector<shared_ptr<ActionObj>> _actions;
    bool _isRun = false;
    bool _isLoop = false;
    int _index = 0;
    
public:
    Action(const std::shared_ptr<GameObject>& gameObjectPtr);
    virtual ~Action(){}
    
    virtual void update() override;
    
    void addRotateBy(const float time, const Vector3 axis,const float rad,const Lerp::rate lerpRate = Lerp::rate::Linear);
    void addMoveTo(const float time, const Vector3 endPos,const Lerp::rate lerpRate = Lerp::rate::Linear);
    
    void run();
    void stop();
    bool getIsRunning(){return _isRun;}
    void actionClear();
    bool getFinished(){return !_isRun;}
};

#endif /* Action_hpp */
