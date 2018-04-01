//
//  3DTestObject.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/03/11.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef _DTestObject_hpp
#define _DTestObject_hpp

#include "river.h"

class TestObject : public GameObject
{
    GLProgram* _useProgram;
    
    GLint attr_pos;
    GLint attr_normal;
    GLint unif_color;
    GLint unif_lookat;
    GLint unif_projection;
    GLint unif_world;
    GLint unif_lightDir;
    
    shared_ptr<MeshResource<PositionNormal>> _testMesh;
    
    float _rot = 0;
public:
    TestObject();
    virtual ~TestObject();
    
    static std::shared_ptr<TestObject> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
};

#endif /* _DTestObject_hpp */
