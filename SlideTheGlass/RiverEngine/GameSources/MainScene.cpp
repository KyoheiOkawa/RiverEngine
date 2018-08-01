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
#include "JudgePocket.hpp"
#include "MainUI.hpp"
#include "MainUICanvas.hpp"
#include "Confetti.hpp"
#include "Picture.hpp"
#include "Wall.hpp"

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
    
    auto director = Director::getInstance();
    director->registerTexture("TABLE_TX", "table.png");
    director->registerTexture("STG_TX", "STG.png");
    director->registerTexture("NUMBERS_TX", "Numbers.png");
    director->registerTexture("GLASS_SP", "GlassSprite.png");
    director->registerTexture("GLASS_NONE_SP", "GlassBatsu.png");
    director->registerTexture("HIGHSCORE_UI", "highScore.png");
    director->registerTexture("RANK_UI", "Rank.png");
    director->registerTexture("PICTURE_TX", "pictureframe.png");
    director->registerTexture("WALL_TX", "Wall.png");
    
    auto audioEngine = SimpleAudioEngine::getInstance();
    audioEngine->registerBgm("Assets/blend", "MAIN_BGM");
    audioEngine->registerSe("Assets/glass_break", "GLASS_BREAK");
    audioEngine->registerSe("Assets/GlassSlide", "GLASS_SLIDE");
    audioEngine->registerSe("Assets/glassTakeOn", "GLASS_ON");
    audioEngine->registerSe("Assets/Excellent", "EXCELLENT");
    audioEngine->registerSe("Assets/Good", "GOOD");
    audioEngine->registerSe("Assets/HighScore", "HIGH_SCORE");
    audioEngine->registerSe("Assets/Nice", "NICE");
    audioEngine->registerSe("Assets/OhMan", "OH_MAN");
    audioEngine->registerSe("Assets/OhYeah", "OH_YEAH");
    audioEngine->registerSe("Assets/OK", "OK");
    audioEngine->registerSe("Assets/Oops", "OOPS");
    audioEngine->startBgm("MAIN_BGM",0.5f,AL_TRUE);
    
    auto userDef = UserDefaults::getInstance();
    if(userDef->getBool("IsStart"))
    {
        _nowScore = (unsigned int)userDef->getInt("BefScore");
        _leftGlassCount = (unsigned int)userDef->getInt("BefLeftGlass");
    }
    else
    {
        _nowScore = 0;
        _leftGlassCount = 3;
    }
    
    auto wall = Wall::create();
    wall->getTransform()->setPosition(Vector3(0,-1.0f,-3.7f));
    wall->getTransform()->setScale(Vector3(0.6f,0.6f,0.6f));
    addGameObject(wall);
    
    auto picture = Picture::create();
    picture->getTransform()->setPosition(Vector3(0,1.5f,-3.5f));
    picture->getTransform()->setScale(Vector3(2.5f,2.5f,2.5f));
    addGameObject(picture);
    
    auto table = Table::create();
    table->getTransform()->setPosition(Vector3(0,-0.5f,0));
    table->getTransform()->setScale(Vector3(1.75f,1.75f,1.75f));
    table->getTransform()->setRotation(Quaternion(Vector3(0,1,0), Deg2Rad(270)));
    addGameObject(table);
    
    auto highScoreUI = HighScoreUI::create();
    addGameObject(highScoreUI);

//    auto stg = STGWord::create();
//    stg->getTransform()->setPosition(Vector3(0,1.3f,-1.5f));
//    stg->getTransform()->setScale(Vector3(0.4f,0.4f,0.4f));
//    addGameObject(stg);

    auto glass = Glass::create();
    addGameObject(glass);
    
    auto judgePocket = JudgePocket::create();
    addGameObject(judgePocket);
    
    float width = Application::getInstance()->getSurfaceWidth();
    float height = Application::getInstance()->getSurfaceHeight();
    float ratioX = height / 1136.0f;
    float ratioY = width / 640.0f;
    
    _scoreNumber = NumberSprite::create("NUMBERS_TX", 0);
    _scoreNumber->getTransform()->setPosition(Vector3(width/ 2.0f,height / 9.0f,0.0f));
    _scoreNumber->getTransform()->setScale(Vector3(ratioX,ratioX,1));
    addGameObject(_scoreNumber);
    _scoreNumber->setDrawLayer(5);
    if(userDef->getBool("IsStart"))
    {
        _scoreNumber->changeNumber((unsigned int)userDef->getInt("BefScore"));
    }
    
    for(int i = 0; i < _maxLeftGlassCount; i++)
    {
        auto sp = Sprite::createWithTexture("GLASS_SP");
        float d = height / 16.0f;
        sp->getTransform()->setPosition(Vector3(50.0f+80*i,height-d,0.0f));
        addGameObject(sp);
        _leftGlassSprites.push_back(sp);
    }
    
    auto uiCanvas = MainUICanvas::create();
    addGameObject(uiCanvas);
    
    ConfettiFragment::InitParam init;
    init._color = Color4(1,1,1,0.5f);
    init._scale = 64;
    init._startPos = Vector3(width/2.0f,0.0f,0.0f);
    init._fallSpeed = 256.0f;
    init._force = Vector2(56,0);
    init._angularVelocity = Deg2Rad(90);
    init._smallSpeed = 16;
    
    auto conf = ConfettiFragment::create(init);
    addGameObject(conf);
    
    if(!userDef->getBool("IsStart"))
    {
        userDef->setInt(3, "BefLeftGlass");
        userDef->setBool(true, "IsStart");
    }
    
    refleshLeftGlassSprites();
    
    LeaderBoardUtil::getInstance()->sendScore(userDef->getInt("HighScore"));
    
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

void MainScene::refleshLeftGlassSprites()
{
    for(int i = _maxLeftGlassCount - 1; i >= 0; i--)
    {
        if(i+1 > _leftGlassCount)
            _leftGlassSprites[i]->setTexture("GLASS_NONE_SP");
        else
            _leftGlassSprites[i]->setTexture("GLASS_SP");
    }
}
