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
    
    auto trans = getTransform();
    _defaultPosition = Vector3(0,0.796f,0.75f);
    trans->setPosition(_defaultPosition);
    
    auto action = addComponent<Action>();
    
    addTag("Glass");
    
    return true;
}

void Glass::update()
{
    physicUpdate();
    
    if(!_touchParam._isTouching &&
       (_state==State::STAY || _state==State::PULL))
        pullToDefaultPos();
    
    if(_state == State::SLIDE)
    {
        Vector3 nowPos = getTransform()->getPosition();
        Vector3 velocityXZ = _physicParam._velocity;
        velocityXZ.y = 0.0f;
        auto action = getComponent<Action>();
        if((nowPos.x > -0.5f && nowPos.x < 0.5f) &&
           (nowPos.z > -1.1f && nowPos.z < 1.055))
        {
            if(velocityXZ.magnitude() < 0.01f)
                startRespawn();
        }
        else
        {
            if(getTransform()->getPosition().y < -2.0f)
                startRespawn();
        }
    }
    
    switch (_state)
    {
        case State::RESPAWN:
            respawn();
            break;
        case State::SLIDE:
            fall();
            break;
    }
    
//    printf("%f\n",Rad2Deg(getTransform()->getRotation().toRotVec().x));
//    printf((getComponent<Action>()->getIsRunning())?"true\n" : "false\n");
    //printf("%f\n",Random::getInstance()->range(0.0f, 1.0f));
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
    
    //PrimitiveDraws::drawPlaneCircle(trans->getPosition() + Vector3(0,0.1f,0), 0.25f, Color4(1,1,1,0.6f));
}

void Glass::onScreenTouched(TouchInfo &info)
{
    switch (info.type) {
        case TouchType::BEGAN:
            _touchParam._isTouching = true;
            break;
        case TouchType::MOVED:
            
            break;
        case TouchType::ENDED:
            _touchParam._isTouching = false;
            break;
    }
    
    slideInput(info);
}

void Glass::slideInput(TouchInfo& info)
{
    if((_state != State::STAY) &&
       (_state != State::PULL))
        return;
    
    float delta = Application::getInstance()->getDeltaTime();
    auto trans = getTransform();
    
    switch(info.type)
    {
        case TouchType::BEGAN:
        {
            _touchParam._start.x = info.posX;
            _touchParam._start.y = info.posY;
            _touchParam._fulcrum = _touchParam._start;
            
            _touchParam._frickTime = 0.0f;
            
            _touchParam._touchStartGlassPos = trans->getPosition();
        }
            break;
        case TouchType::MOVED:
        {
            _touchParam._frickTime += delta;
            
            if(_touchParam._frickTime >= _touchParam._maxFrickTime)
            {
                _touchParam._frickTime = 0.0f;
                _touchParam._fulcrum.x = info.posX;
                _touchParam._fulcrum.y = info.posY;
            }
            
            Vector3 dir;
            dir.x = info.posX - _touchParam._start.x;
            dir.y = _defaultPosition.y;
            dir.z = info.posY - _touchParam._start.y;
            
            trans->setPosition(_touchParam._touchStartGlassPos+dir*_touchParam._touchMoveGlassRadius);
        }
            break;
        case TouchType::ENDED:
        {
            _touchParam._end.x = info.posX;
            _touchParam._end.y = info.posY;
            
            Vector2 dir = _touchParam._end - _touchParam._fulcrum;
            float slideLen = dir.magnitude();
            
            //フリックした長さが短い場合は滑らせない
            float minLen = 100.0f;
            if(slideLen <= minLen)
                break;
            
            _state = State::SLIDE;
            
            float power = slideLen * _touchParam._slidePower;
            float speed = 1.0f / ((1.0f-_touchParam._maxFrickTime)+_touchParam._frickTime);
            
            _physicParam._velocity.x = dir.getNormalized().x * power;
            _physicParam._velocity.z = dir.getNormalized().y * power;
            
            _isRunFallAction = false;
        }
            break;
    }
}

void Glass::physicUpdate()
{
    float delta = Application::getInstance()->getDeltaTime();
    
    if(delta > 1.0f)
        return;
    
    auto trans = getTransform();
    Vector3 nowPos = trans->getPosition();
    
    nowPos += _physicParam._velocity * delta;
    
    _physicParam._velocity *= _physicParam._friction;
    trans->setPosition(nowPos);
}

void Glass::pullToDefaultPos()
{
    float delta = Application::getInstance()->getDeltaTime();
    auto trans = getTransform();
    Vector3 dir = _defaultPosition - trans->getPosition();
    
    if(dir.magnitude() > 0.001f)
    {
        _state = State::PULL;
        
        Vector3 nowPos = trans->getPosition();
        nowPos += dir * delta * _pullPower;
        trans->setPosition(nowPos);
    }
    else
    {
        _state = State::STAY;
    }
}

void Glass::respawn()
{
    float delta = Application::getInstance()->getDeltaTime();
    auto trans = getTransform();
    
    _physicParam._velocity.y -= 9.8f * delta;
    
    if(trans->getPosition().y <= _defaultPosition.y)
    {
        trans->setPosition(_defaultPosition);
        _physicParam._velocity = Vector3::ZERO();
        _state = State::STAY;
    }
}

void Glass::fall()
{
    float delta = Application::getInstance()->getDeltaTime();
    auto trans = getTransform();
    Vector3 nowPos = trans->getPosition();
    
    if((nowPos.x > -0.5f && nowPos.x < 0.5f) &&
       (nowPos.z > -1.1f && nowPos.z < 1.055))
        return;
    
    auto action = getComponent<Action>();
    if(!action->getIsRunning() && !_isRunFallAction)
    {
        if(nowPos.x < -0.5f)
        {
            action->addRotateBy(1.0f, Vector3::FORWARD(), Deg2Rad(90),Lerp::Easein);
            action->run();
            _isRunFallAction = true;
        }
        else if(nowPos.x > 0.5f)
        {
            action->addRotateBy(1.0f, Vector3::FORWARD(), Deg2Rad(-90),Lerp::Easein);
            action->run();
            _isRunFallAction = true;
        }
        else if(nowPos.z < -1.1f)
        {
            action->addRotateBy(1.0f, Vector3::RIGHT(), Deg2Rad(-90),Lerp::Easein);
            action->run();
            _isRunFallAction = true;
        }
        else if(nowPos.z > 1.055f)
        {
            action->addRotateBy(1.0f, Vector3::RIGHT(), Deg2Rad(90),Lerp::Easein);
            action->run();
            _isRunFallAction = true;
        }
    }

    if((nowPos.x > -0.58f && nowPos.x < -0.5f)   ||
        (nowPos.x < 0.58f && nowPos.x > 0.5f)    ||
        (nowPos.z > -1.14f  && nowPos.z < -1.1f) ||
        (nowPos.z < 1.12f && nowPos.z > 1.055f))
    {
        Vector3 nowRot = trans->getRotation().toRotVec();
        if(fabsf(Rad2Deg(nowRot.z)) > 60.0f ||
           fabsf(Rad2Deg(nowRot.x)) > 60.0f)
        {
            _physicParam._velocity.y -= 9.8f * delta;
        }
    }
    else
    {
        _physicParam._velocity.y -= 9.8f * delta;
    }
}

void Glass::startRespawn()
{
    _state = State::RESPAWN;
    Vector3 setPos = _defaultPosition;
    setPos.y += 1.5f;
    getTransform()->setPosition(setPos);
    getTransform()->setRotation(Quaternion::identity());
    
    auto action = getComponent<Action>();
    action->stop();
    action->actionClear();
}
