//
//  MainUI.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/19.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "MainUI.hpp"

HighScoreUI::HighScoreUI()
{
    
}

std::shared_ptr<HighScoreUI> HighScoreUI::create()
{
    shared_ptr<HighScoreUI> ret(new HighScoreUI());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool HighScoreUI::init()
{
    GameObject::init();
    
    //float width = Application::getInstance()->getSurfaceWidth();
    //float height = Application::getInstance()->getSurfaceHeight();
    
    _wordSprite = Sprite::createWithTexture("HIGHSCORE_UI");
    //_wordSprite->getTransform()->setPosition(Vector3(width/2.0f,height/2.0f-(height/4.0f)+width*3/16.0f,0.0f));
    _wordSprite->setIs3DWorld(true);
    _wordSprite->getTransform()->setPosition(Vector3(0,0.7f,-3.5f));
    _wordSprite->getTransform()->setScale(Vector3(4*0.3f,1*0.3f,1));
    
    int highScore = UserDefaults::getInstance()->getInt("HighScore");
    
    _score = NumberSprite::create("NUMBERS_TX", (unsigned int)highScore);
    _score->setIs3DWorld(true);
    _score->getTransform()->setPosition(Vector3(0,0.35f,-3.5f));
    //_score->getTransform()->setPosition(Vector3(width/2.0f,height/2.0f-(height/4.0f)+60.0f+width*3/16.0f,0.0f));
    _score->getTransform()->setScale(Vector3(0.4f,0.4f,0.4f));
    
    addTag("HighScoreUI");
    addTag("GlassOST");
    
    return true;
}

void HighScoreUI::update()
{
    
}

void HighScoreUI::draw()
{
    _wordSprite->draw();
    _score->draw();
}

void HighScoreUI::setHighScore(unsigned int score)
{
    int highScore = UserDefaults::getInstance()->getInt("HighScore");
    if((int)score > highScore)
    {
        UserDefaults::getInstance()->setInt((int)score, "HighScore");
        _score->changeNumber(score);
        LeaderBoardUtil::getInstance()->sendScore((int)score);
    }
}
