//
//  Picture.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/27.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Picture_hpp
#define Picture_hpp

#include "river.h"

class Picture : public GameObject
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
    
    shared_ptr<MeshResource<PositionNormalTexture>> _mesh;
public:
    Picture();
    virtual ~Picture();
    
    static std::shared_ptr<Picture> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
};

#endif /* Picture_hpp */
