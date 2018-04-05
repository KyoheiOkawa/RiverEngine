//
//  HelloWorldScene.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "HelloWorldScene.hpp"
#include "3DTestObject.hpp"

HelloWorldScene::HelloWorldScene()
{
    
}

HelloWorldScene::~HelloWorldScene()
{
    
}

std::shared_ptr<Scene> HelloWorldScene::createScene()
{
    auto ret = std::shared_ptr<HelloWorldScene>(new HelloWorldScene());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool HelloWorldScene::init()
{
    if(!Scene::init())
        return false;
    
    auto director = Director::getInstance();
    auto audioEngine = SimpleAudioEngine::getInstance();
    audioEngine->registerBgm("Assets/Why", "BGM_WHY");
    audioEngine->registerSe("Assets/cursor", "SE_CURSOR");
    audioEngine->startBgm("BGM_WHY",1.0f,AL_TRUE);
    
    auto sprite = Sprite::createWithTexture("River.png");
    this->addGameObject(sprite);

    auto sprite2 = Sprite::createWithTexture("blendTex.png");
    sprite2->getTransform()->setPosition(Vector3(0,600,0));
    this->addGameObject(sprite2);
    
    auto triangle = TestObject::create();
    triangle->setDrawLayer(-1);
    this->addGameObject(triangle);
    
    return true;
}

void HelloWorldScene::update()
{
    
}

void HelloWorldScene::draw()
{
    Scene::draw();
}

void HelloWorldScene::onScreenTouched(TouchInfo &touchInfo)
{
    Scene::onScreenTouched(touchInfo);
    
    if(touchInfo.type == TouchType::BEGAN)
    {
        auto audioEngine = SimpleAudioEngine::getInstance();
        audioEngine->startSe("SE_CURSOR", 1.0f);
    }
}
