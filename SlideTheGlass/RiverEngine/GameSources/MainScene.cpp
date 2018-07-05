//
//  HelloWorldScene.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "MainScene.hpp"
#include "3DTestObject.hpp"
#include "Table.hpp"
#include "Glass.hpp"
#include "STGWord.hpp"

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
    
    Director::getInstance()->registerTexture("TABLE_TX", "table.png");
    Director::getInstance()->registerTexture("STG_TX", "STG.png");
    
    auto table = Table::create();
    table->getTransform()->setPosition(Vector3(0,-0.5f,0));
    table->getTransform()->setScale(Vector3(1.75f,1.75f,1.75f));
    table->getTransform()->setRotation(Quaternion(Vector3(0,1,0), Deg2Rad(270)));
    addGameObject(table);
    
    auto stg = STGWord::create();
    stg->getTransform()->setPosition(Vector3(0,1.25f,-1.5f));
    stg->getTransform()->setScale(Vector3(0.5f,0.5f,0.5f));
    addGameObject(stg);
    
    auto glass = Glass::create();
    addGameObject(glass);
    
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
