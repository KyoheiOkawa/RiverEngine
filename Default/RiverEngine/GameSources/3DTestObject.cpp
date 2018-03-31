//
//  3DTestObject.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/03/11.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "3DTestObject.hpp"

TestObject::TestObject()
{
    
}

TestObject::~TestObject()
{
    
}

shared_ptr<TestObject> TestObject::create()
{
    shared_ptr<TestObject> ret(new TestObject());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool TestObject::init()
{
    _useProgram = Director::getInstance()->getGLProgram("PStatic");
    
    attr_pos = _useProgram->getAttribLocation("attr_pos");
    
    unif_color = _useProgram->getUnifLocation("unif_color");
    
    unif_lookat = _useProgram->getUnifLocation("unif_lookat");
    
    unif_projection = _useProgram->getUnifLocation("unif_projection");
    
    _testMesh = MeshResource<PositionNormal>::createWithFile("Assets/Cube");
    auto vertex = _testMesh->GetVertexPointer();
    for(int i = 0; i < _testMesh->GetVertexCount(); i++)
    {
        printf("%04d : %+f, %+f, %+f",i,vertex[i].position[0],vertex[i].position[1],vertex[i].position[2]);
        printf(" / %+f, %+f, %+f\n",vertex[i].normal[0],vertex[i].normal[1],vertex[i].normal[2]);
    }
    
    return true;
}

void TestObject::update()
{
    static float testObjDir = 1.0f;
    
    auto cam = Director::getInstance()->getScene()->GetMainCamera();
    Vector3 pos = cam->GetCameraPos();
    pos.x += 0.01f * testObjDir;
    cam->SetCameraPos(pos);
    
    if(abs(pos.x) > 5.0f)
        testObjDir *= -1.0f;
}

void TestObject::draw()
{
    auto app = Application::getInstance();
    
    _useProgram->use();
    glEnable(GL_DEPTH_TEST);
    glEnableVertexAttribArray(attr_pos);
    assert(glGetError()==GL_NO_ERROR);
    
    Matrix4x4 lookAt,projection;
    Director::getInstance()->getScene()->GetMainCamera()->GetLookAtProjection(lookAt, projection);

    glUniformMatrix4fv(unif_lookat, 1, GL_FALSE, lookAt.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniformMatrix4fv(unif_projection, 1, GL_FALSE, projection.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniform4f(unif_color, 1.0f, 1.0f, 1.0f, 1.0f);
    assert(glGetError()==GL_NO_ERROR);
    
    const GLfloat positionTriangle[] = {
        0.0f,0.5f,-0.55f,
        -0.5f,0.0f,-0.55f,
        0.5f,0.0f,-0.55f
    };
    
    glVertexAttribPointer(attr_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) positionTriangle);
    assert(glGetError()==GL_NO_ERROR);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    assert(glGetError()==GL_NO_ERROR);
    
    glUniform4f(unif_color, 1.0f, 0.0f, 0.0f, 1.0f);
    
    glVertexAttribPointer(attr_pos, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormal), (GLvoid*)_testMesh->GetVertexPointer());
    assert(glGetError()==GL_NO_ERROR);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_testMesh->GetVertexCount());
    assert(glGetError()==GL_NO_ERROR);
    
    glDisable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(attr_pos);
    assert(glGetError()==GL_NO_ERROR);
}














