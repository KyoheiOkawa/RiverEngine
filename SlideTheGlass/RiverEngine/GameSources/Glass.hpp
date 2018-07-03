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
        Vector2 _end;
        float _frickTime;
        
        const float _maxFrickTime = 0.5f;
        const float _slidePower = 0.005f;
        const float _touchMoveGlassRadius = 0.0001f;
        
        TouchParam():
        _start(Vector2(0,0)),
        _end(Vector2(0,0)),
        _frickTime(0.0f){}
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
    
    Vector3 _defaultPosition;
    
    void physicUpdate();
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
