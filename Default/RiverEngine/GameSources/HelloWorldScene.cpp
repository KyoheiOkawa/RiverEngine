//
//  HelloWorldScene.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "HelloWorldScene.hpp"

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
    director->registerTexture("RIVER_TX", "River.png");
    director->registerTexture("ANGRY_TX", "nPodTex.png");
    
    auto sprite = Sprite::create();
    sprite->setTexture("RIVER_TX");
    this->addGameObject(sprite);
    
    auto sprite2 = Sprite::create();
    sprite2->getTransform()->setPosition(Vector3(0,600,0));
    sprite2->setTexture("ANGRY_TX");
    this->addGameObject(sprite2);
    
    return true;
}

void HelloWorldScene::update()
{
    
}

void HelloWorldScene::draw()
{
    Scene::draw();
}
