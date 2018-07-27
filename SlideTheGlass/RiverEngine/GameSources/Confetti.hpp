//
//  Confetti.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/25.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Confetti_hpp
#define Confetti_hpp

#include "river.h"

class ConfettiFragment : public GameObject
{
public:
    struct InitParam
    {
        float _angularVelocity;
        float _fallSpeed;
        float _smallSpeed;
        float _scale;
        Vector2 _force;
        Color4 _color;
        Vector3 _startPos;
    };
    
private:
    InitParam _initParam;
    
    GLProgram* _useProgram;
    GLint _attr_pos;
    GLint _unif_color;
    GLint _unif_matrix;
    
    std::shared_ptr<MeshResource<Position>> _meshResource;
public:
    ConfettiFragment(const InitParam initParam);
    virtual ~ConfettiFragment(){}
    
    static shared_ptr<ConfettiFragment> create(const InitParam initParam);
    
    virtual bool init()override;
    virtual void update()override;
    virtual void draw()override;
};

class ConfettiEmitter : public GameObject
{
    float _emitTime=0;
    const float _emitInterval;
    const float _emitIntervalRandomLength;
    float _emitIntervalCount=0;
    
    void dropConfettiFrag();
public:
    ConfettiEmitter();
    virtual ~ConfettiEmitter(){}
    
    static shared_ptr<ConfettiEmitter> create();
    
    virtual bool init()override;
    virtual void update()override;
    virtual void draw()override;
    
    void emit(float time);
};

#endif /* Confetti_hpp */
