//
//  HelloWorldScene.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "MainScene.hpp"
#include "3DTestObject.hpp"

MainScene::MainScene()
{
    
}

MainScene::~MainScene()
{
    
}

std::shared_ptr<Scene> MainScene::createScene()
{
    auto ret = std::shared_ptr<MainScene>(new MainScene());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool MainScene::init()
{
    if(!Scene::init())
        return false;
    
    return true;
}

void MainScene::update()
{
    
}

void MainScene::draw()
{
    Scene::draw();
}

void MainScene::onScreenTouched(TouchInfo &touchInfo)
{
    Scene::onScreenTouched(touchInfo);
}
