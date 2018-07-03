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

class Glass : public GameObject
{
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
public:
    Glass();
    virtual ~Glass();
    
    static std::shared_ptr<Glass> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
};

#endif /* Glass_hpp */
