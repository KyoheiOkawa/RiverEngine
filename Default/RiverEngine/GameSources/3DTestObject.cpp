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
    cameraPos = Vector3(3,1.5f,-5.0f);
    
    _useProgram = Director::getInstance()->getGLProgram("PStatic");
    
    attr_pos = _useProgram->getAttribLocation("attr_pos");
    
    unif_color = _useProgram->getUnifLocation("unif_color");
    
    unif_lookat = _useProgram->getUnifLocation("unif_lookat");
    
    unif_projection = _useProgram->getUnifLocation("unif_projection");
    
    return true;
}

void TestObject::update()
{
    cameraPos.z += 0.01f;
    
    if(cameraPos.z > 5.0f)
        cameraPos.z = -5.0f;
}

void TestObject::draw()
{
    auto app = Application::getInstance();
    
    _useProgram->use();
    glEnable(GL_DEPTH_TEST);
    glEnableVertexAttribArray(attr_pos);
    assert(glGetError()==GL_NO_ERROR);
    
    const Vector3 camera_pos = cameraPos;
    const Vector3 camera_look = Vector3(0,0,0);
    const Vector3 camera_up = Vector3(0,1,0);
    const Matrix4x4 lookAt = Matrix4x4::createLookAt(camera_pos, camera_look, camera_up);

    const GLfloat prj_near = 1.0f;
    const GLfloat prj_far = 30.0f;
    const GLfloat prj_fovY = 45.0f;
    const GLfloat prj_aspect = (GLfloat)(app->getSurfaceWidth()) / (GLfloat)(app->getSurfaceHeight());
    const Matrix4x4 projection = Matrix4x4::createPerspective(prj_near, prj_far, prj_fovY, prj_aspect);

    glUniformMatrix4fv(unif_lookat, 1, GL_FALSE, lookAt.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniformMatrix4fv(unif_projection, 1, GL_FALSE, projection.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniform4f(unif_color, 1.0f, 1.0f, 1.0f, 1.0f);
    assert(glGetError()==GL_NO_ERROR);
    
    const GLfloat positionTriangle[] = {
        0.0f,0.5f,-0.5f,
        -0.5f,0.0f,-0.5f,
        0.5f,0.0f,-0.5f
    };
    
    glVertexAttribPointer(attr_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) positionTriangle);
    assert(glGetError()==GL_NO_ERROR);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    assert(glGetError()==GL_NO_ERROR);
    
    glDisable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(attr_pos);
    assert(glGetError()==GL_NO_ERROR);
}














