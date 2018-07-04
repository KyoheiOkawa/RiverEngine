//
//  STLWord.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/04.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef STLWord_hpp
#define STLWord_hpp

#include "river.h"

class STGWord : public GameObject
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
    STGWord();
    virtual ~STGWord();
    
    static std::shared_ptr<STGWord> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
};

#endif /* STLWord_hpp */
