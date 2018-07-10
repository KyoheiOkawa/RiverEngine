//
//  Glass.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/03.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Glass_hpp
#define Glass_hpp

#include "river.h"
#include "Project.hpp"

class Glass : public GameObject
{
public:
    struct TouchParam
    {
        Vector2 _start;
        Vector2 _fulcrum;
        Vector2 _end;
        //タッチ開始時のグラスの位置
        Vector3 _touchStartGlassPos;
        float _frickTime;
        bool _isTouching;
        
        const float _maxFrickTime = 0.5f;
        const float _slidePower = 0.008f;
        const float _touchMoveGlassRadius = 0.0003f;
        
        TouchParam():
        _start(Vector2(0,0)),
        _end(Vector2(0,0)),
        _frickTime(0.0f),
        _isTouching(false){}
    };
    
    enum State
    {
        STAY,
        PULL,
        SLIDE,
        RESPAWN
    };
private:
    
    GLProgram* _useProgram;
    
    GLint attr_pos;
    GLint attr_normal;
    GLint attr_uv;
    GLint unif_color;
    GLint unif_lookat;
    GLint unif_projection;
    GLint unif_world;
    GLint unif_lightDir;
    GLuint textureId;
    
    shared_ptr<MeshResource<PositionNormal>> _mesh;
    
    Matrix4x4 _meshTransform;
    
    PhysicParam _physicParam;
    TouchParam _touchParam;
    float _pullPower = 5.0f;
    
    Vector3 _defaultPosition;
    
    State _state = State::STAY;
    
    bool _isRunFallAction = false;
    
    void physicUpdate();
    void slideInput(TouchInfo& info);
    void pullToDefaultPos();
    void respawn();
    //手前1.055/1.12 奥-1.1/-1.14 左-0.5/-0.58　右0.5/0.58
    void fall();
    
    void startRespawn();
public:
    Glass();
    virtual ~Glass();
    
    static std::shared_ptr<Glass> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void onScreenTouched(TouchInfo& info)override;
};

#endif /* Glass_hpp */
