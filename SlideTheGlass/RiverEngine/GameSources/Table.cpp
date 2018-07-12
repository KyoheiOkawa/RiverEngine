//
//  Table.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/03.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Table.hpp"

Table::Table()
{
    
}

Table::~Table()
{
    
}

shared_ptr<Table> Table::create()
{
    shared_ptr<Table> ret(new Table());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool Table::init()
{
    if(!GameObject::init())
        return false;
    
    _useProgram = Director::getInstance()->getGLProgram("PNTStatic");
    
    attr_pos = _useProgram->getAttribLocation("attr_pos");
    
    attr_normal = _useProgram->getAttribLocation("attr_normal");
    
    attr_uv = _useProgram->getAttribLocation("attr_uv");
    
    unif_color = _useProgram->getUnifLocation("unif_color");
    
    unif_lookat = _useProgram->getUnifLocation("unif_lookat");
    
    unif_projection = _useProgram->getUnifLocation("unif_projection");
    
    unif_world = _useProgram->getUnifLocation("unif_world");
    
    unif_lightDir = _useProgram->getUnifLocation("unif_lightDir");
    
    _mesh = MeshResource<PositionNormalTexture>::createWithFile("Assets/table");
    
    auto texInfo = Director::getInstance()->getRegesterdTextureInfo("TABLE_TX");
    textureId = texInfo->id;
    
    return true;
}

void Table::update()
{

}

void Table::draw()
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
    
    Vector3 light(-1.0f,-1.0f,1.0f);
    light.normalize();
    glUniform3f(unif_lightDir, light.x, light.y, light.z);
    assert(glGetError()==GL_NO_ERROR);
    
    glVertexAttribPointer(attr_pos, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTexture), (GLvoid*)((GLubyte*)_mesh->GetVertexPointer()));
    assert(glGetError()==GL_NO_ERROR);
    glVertexAttribPointer(attr_normal, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTexture), (GLvoid*)((GLubyte*)_mesh->GetVertexPointer() + sizeof(GLfloat)*3));
    assert(glGetError()==GL_NO_ERROR);
    glVertexAttribPointer(attr_uv, 2, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTexture), (GLvoid*)((GLubyte*)_mesh->GetVertexPointer() + sizeof(GLfloat)*6));
    assert(glGetError()==GL_NO_ERROR);
    
    glBindTexture(GL_TEXTURE_2D, textureId);

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_mesh->GetVertexCount());
    assert(glGetError()==GL_NO_ERROR);
    
    glDisable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(attr_pos);
    glDisableVertexAttribArray(attr_normal);
    glDisableVertexAttribArray(attr_uv);
    assert(glGetError()==GL_NO_ERROR);
}