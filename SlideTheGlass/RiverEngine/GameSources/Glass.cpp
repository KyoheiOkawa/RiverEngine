//
//  Glass.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/03.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Glass.hpp"

Glass::Glass()
{
    
}

Glass::~Glass()
{
    
}

shared_ptr<Glass> Glass::create()
{
    shared_ptr<Glass> ret(new Glass());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool Glass::init()
{
    if(!GameObject::init())
        return false;
    
    _useProgram = Director::getInstance()->getGLProgram("PNStatic");
    
    attr_pos = _useProgram->getAttribLocation("attr_pos");
    
    attr_normal = _useProgram->getAttribLocation("attr_normal");
    
    unif_color = _useProgram->getUnifLocation("unif_color");
    
    unif_lookat = _useProgram->getUnifLocation("unif_lookat");
    
    unif_projection = _useProgram->getUnifLocation("unif_projection");
    
    unif_world = _useProgram->getUnifLocation("unif_world");
    
    unif_lightDir = _useProgram->getUnifLocation("unif_lightDir");
    
    _mesh = MeshResource<PositionNormal>::createWithFile("Assets/glass");
    
    _meshTransform = Matrix4x4::createScale(0.25f, 0.25f, 0.25f);
    
    return true;
}

void Glass::update()
{

}

void Glass::draw()
{
    auto app = Application::getInstance();
    
    _useProgram->use();
    glEnable(GL_DEPTH_TEST);
    glEnableVertexAttribArray(attr_pos);
    glEnableVertexAttribArray(attr_normal);
    assert(glGetError()==GL_NO_ERROR);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    Matrix4x4 lookAt,projection;
    Director::getInstance()->getScene()->GetMainCamera()->GetLookAtProjection(lookAt, projection);
    
    Matrix4x4 pos,scale,rot;
    auto trans = getTransform();
    pos = Matrix4x4::createTranslate(trans->getPosition().x, trans->getPosition().y, trans->getPosition().z);
    scale = Matrix4x4::createScale(trans->getScale().x, trans->getScale().y, trans->getScale().z);
    rot = Matrix4x4::createRotate(trans->getRotation());
    Matrix4x4 world = pos * scale * rot;
    world *= _meshTransform;
    
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
    
    glVertexAttribPointer(attr_pos, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormal), (GLvoid*)_mesh->GetVertexPointer());
    assert(glGetError()==GL_NO_ERROR);
    glVertexAttribPointer(attr_normal, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormal), (GLvoid*)((GLubyte*)_mesh->GetVertexPointer() + sizeof(GLfloat)*3));
    assert(glGetError()==GL_NO_ERROR);
    
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_mesh->GetVertexCount());
    assert(glGetError()==GL_NO_ERROR);
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisableVertexAttribArray(attr_pos);
    glDisableVertexAttribArray(attr_normal);
    assert(glGetError()==GL_NO_ERROR);
}
