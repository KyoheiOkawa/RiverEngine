//
//  Table.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/03.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp

#include "river.h"

class Table : public GameObject
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
    
    shared_ptr<MeshResource<PositionNormal>> _testMesh;
public:
    Table();
    virtual ~Table();
    
    static std::shared_ptr<Table> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
};

#endif /* Table_hpp */
