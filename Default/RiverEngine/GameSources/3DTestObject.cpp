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
    if(!GameObject::init())
        return false;
    
    _useProgram = Director::getInstance()->getGLProgram("PStatic");
    
    attr_pos = _useProgram->getAttribLocation("attr_pos");
    
    attr_normal = _useProgram->getAttribLocation("attr_normal");
    
    unif_color = _useProgram->getUnifLocation("unif_color");
    
    unif_lookat = _useProgram->getUnifLocation("unif_lookat");
    
    unif_projection = _useProgram->getUnifLocation("unif_projection");
    
    unif_world = _useProgram->getUnifLocation("unif_world");
    
    unif_lightDir = _useProgram->getUnifLocation("unif_lightDir");
    
    _testMesh = MeshResource<PositionNormal>::createWithFile("Assets/glass");
    getTransform()->setPosition(Vector3(0,1.0f,0.0f));
//    auto vertex = _testMesh->GetVertexPointer();
//    for(int i = 0; i < _testMesh->GetVertexCount(); i++)
//    {
//        printf("%04d : %+f, %+f, %+f",i,vertex[i].position[0],vertex[i].position[1],vertex[i].position[2]);
//        printf(" / %+f, %+f, %+f\n",vertex[i].normal[0],vertex[i].normal[1],vertex[i].normal[2]);
//    }
    
    return true;
}

void TestObject::update()
{
//    static float testObjDir = 1.0f;
//
//    auto cam = Director::getInstance()->getScene()->GetMainCamera();
//    Vector3 pos = cam->GetCameraPos();
//    pos.x += 0.01f * testObjDir;
//    cam->SetCameraPos(pos);
//
//    if(abs(pos.x) > 5.0f)
//        testObjDir *= -1.0f;
    
    float deltaTime = Application::getInstance()->getDeltaTime();

    static float testObjMoveDir = 1.0f;
    auto trans = getTransform();
    trans->translate(Vector3(deltaTime * testObjMoveDir,0,0));
    if(abs(trans->getPosition().x) > 1.0f)
    {
        trans->setPosition(Vector3(testObjMoveDir,1.0f,0));
        testObjMoveDir *= -1.0f;
    }
    
    trans->rotate(Vector3(1,1,0), Deg2Rad(90 * deltaTime));
}

void TestObject::draw()
{
    auto app = Application::getInstance();
    
    _useProgram->use();
    glEnable(GL_DEPTH_TEST);
    glEnableVertexAttribArray(attr_pos);
    glEnableVertexAttribArray(attr_normal);
    assert(glGetError()==GL_NO_ERROR);
    
    Matrix4x4 lookAt,projection;
    Director::getInstance()->getScene()->GetMainCamera()->GetLookAtProjection(lookAt, projection);
    
    Matrix4x4 pos,scale,rot;
    auto trans = getTransform();
    pos = Matrix4x4::createTranslate(trans->getPosition().x, trans->getPosition().y, trans->getPosition().z);
    scale = Matrix4x4::createScale(trans->getScale().x, trans->getScale().y, trans->getScale().z);
    rot = Matrix4x4::createRotate(trans->getRotation());
    Matrix4x4 world = pos * scale * rot;

    glUniformMatrix4fv(unif_lookat, 1, GL_FALSE, lookAt.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniformMatrix4fv(unif_projection, 1, GL_FALSE, projection.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniformMatrix4fv(unif_world, 1, GL_FALSE, world.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniform4f(unif_color, 1.0f, 1.0f, 1.0f, 1.0f);
    assert(glGetError()==GL_NO_ERROR);
    
    Vector3 light(-1.0f,-1.0f,-1.0f);
    light.normalize();
    glUniform3f(unif_lightDir, light.x, light.y, light.z);
    assert(glGetError()==GL_NO_ERROR);
    
    glVertexAttribPointer(attr_pos, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormal), (GLvoid*)_testMesh->GetVertexPointer());
    assert(glGetError()==GL_NO_ERROR);
    glVertexAttribPointer(attr_normal, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormal), (GLvoid*)((GLubyte*)_testMesh->GetVertexPointer() + sizeof(GLfloat)*3));
    assert(glGetError()==GL_NO_ERROR);
    
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_testMesh->GetVertexCount());
    assert(glGetError()==GL_NO_ERROR);
    
    glDisable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(attr_pos);
    glDisableVertexAttribArray(attr_normal);
    assert(glGetError()==GL_NO_ERROR);
}

TestObject2::TestObject2()
{
    
}

TestObject2::~TestObject2()
{
    
}

shared_ptr<TestObject2> TestObject2::create()
{
    shared_ptr<TestObject2> ret(new TestObject2());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool TestObject2::init()
{
    if(!GameObject::init())
        return false;
    
    _useProgram = Director::getInstance()->getGLProgram("PSTtatic");
    
    attr_pos = _useProgram->getAttribLocation("attr_pos");
    
    attr_normal = _useProgram->getAttribLocation("attr_normal");
    
    attr_uv = _useProgram->getAttribLocation("attr_uv");
    
    unif_color = _useProgram->getUnifLocation("unif_color");
    
    unif_lookat = _useProgram->getUnifLocation("unif_lookat");
    
    unif_projection = _useProgram->getUnifLocation("unif_projection");
    
    unif_world = _useProgram->getUnifLocation("unif_world");
    
    unif_lightDir = _useProgram->getUnifLocation("unif_lightDir");
    
    _testMesh = MeshResource<PositionNormal>::createWithFile("Assets/PNTCube");
    
    auto texInfo = Director::getInstance()->getRegesterdTextureInfo("River.png");
    textureId = texInfo->id;
    
    getTransform()->setPosition(Vector3(0.0f,-1.0f,0.0f));
    
    return true;
}

void TestObject2::update()
{
    float deltaTime = Application::getInstance()->getDeltaTime();
    
    static float testObjMoveDir = -1.0f;
    auto trans = getTransform();
    trans->translate(Vector3(deltaTime * testObjMoveDir,0,0));
    if(abs(trans->getPosition().x) > 1.0f)
    {
        trans->setPosition(Vector3(testObjMoveDir,-1.0f,0));
        testObjMoveDir *= -1.0f;
    }
    
    trans->rotate(Vector3(1,1,0), Deg2Rad(90 * deltaTime));
}

void TestObject2::draw()
{
    auto app = Application::getInstance();
    
    _useProgram->use();
    glEnable(GL_DEPTH_TEST);
    glEnableVertexAttribArray(attr_pos);
    glEnableVertexAttribArray(attr_normal);
    glEnableVertexAttribArray(attr_uv);
    assert(glGetError()==GL_NO_ERROR);
    
    Matrix4x4 lookAt,projection;
    Director::getInstance()->getScene()->GetMainCamera()->GetLookAtProjection(lookAt, projection);
    
    Matrix4x4 pos,scale,rot;
    auto trans = getTransform();
    pos = Matrix4x4::createTranslate(trans->getPosition().x, trans->getPosition().y, trans->getPosition().z);
    scale = Matrix4x4::createScale(trans->getScale().x, trans->getScale().y, trans->getScale().z);
    rot = Matrix4x4::createRotate(trans->getRotation());
    Matrix4x4 world = pos * scale * rot;
    
    glUniformMatrix4fv(unif_lookat, 1, GL_FALSE, lookAt.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniformMatrix4fv(unif_projection, 1, GL_FALSE, projection.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniformMatrix4fv(unif_world, 1, GL_FALSE, world.matrix);
    assert(glGetError()==GL_NO_ERROR);
    glUniform4f(unif_color, 1.0f, 1.0f, 1.0f, 1.0f);
    assert(glGetError()==GL_NO_ERROR);
    
    Vector3 light(-1.0f,-1.0f,-1.0f);
    light.normalize();
    glUniform3f(unif_lightDir, light.x, light.y, light.z);
    assert(glGetError()==GL_NO_ERROR);
    
    glVertexAttribPointer(attr_pos, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTexture), (GLvoid*)_testMesh->GetVertexPointer());
    assert(glGetError()==GL_NO_ERROR);
    glVertexAttribPointer(attr_normal, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTexture), (GLvoid*)((GLubyte*)_testMesh->GetVertexPointer() + sizeof(GLfloat)*3));
    assert(glGetError()==GL_NO_ERROR);
    glVertexAttribPointer(attr_uv, 2, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTexture), (GLvoid*)((GLubyte*)_testMesh->GetVertexPointer() + sizeof(GLfloat)*6));
    assert(glGetError()==GL_NO_ERROR);
    
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_testMesh->GetVertexCount());
    assert(glGetError()==GL_NO_ERROR);
    
    glDisable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(attr_pos);
    glDisableVertexAttribArray(attr_normal);
    glDisableVertexAttribArray(attr_uv);
    assert(glGetError()==GL_NO_ERROR);
}













