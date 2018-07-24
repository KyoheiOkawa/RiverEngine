//
//  HelloWorldScene.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef HelloWorldScene_hpp
#define HelloWorldScene_hpp

#include <stdio.h>
#include "river.h"

class MainScene : public Scene
{
    unsigned int _nowScore = 0;
    shared_ptr<NumberSprite> _scoreNumber;
    
    const unsigned int _maxLeftGlassCount = 3;
    unsigned int _leftGlassCount = 3;
    vector<shared_ptr<Sprite>> _leftGlassSprites;
public:
    MainScene();
    virtual ~MainScene();
    
    static std::shared_ptr<Scene> createScene();
    
    virtual bool init() override;
    
    virtual void update() override;
    
    virtual void draw() override;
    
    virtual void onScreenTouched(TouchInfo& touchInfo)override;
    
    void addScore(unsigned int score)
    {
        _nowScore += score;
        _scoreNumber->changeNumber(_nowScore);
        UserDefaults::getInstance()->setInt((int)_nowScore, "BefScore");
    }
    void resetScore()
    {
        _nowScore = 0;
        _scoreNumber->changeNumber(_nowScore);
        UserDefaults::getInstance()->setInt((int)_nowScore, "BefScore");
    }
    unsigned int getScore(){return _nowScore;}
    
    void decLeftGlass()
    {
        if(_leftGlassCount <= 0)
            _leftGlassCount = 0;
        else
            _leftGlassCount--;
        
        UserDefaults::getInstance()->setInt((int)_leftGlassCount, "BefLeftGlass");
        refleshLeftGlassSprites();
    }
    
    void incLeftGlass()
    {
        _leftGlassCount++;
        if(_leftGlassCount > _maxLeftGlassCount)
            _leftGlassCount = _maxLeftGlassCount;
        
        UserDefaults::getInstance()->setInt((int)_leftGlassCount, "BefLeftGlass");
        refleshLeftGlassSprites();
    }
    
    void resetLeftGlassCount()
    {
        _leftGlassCount = _maxLeftGlassCount;
        UserDefaults::getInstance()->setInt((int)_leftGlassCount, "BefLeftGlass");
        refleshLeftGlassSprites();
    }
    
    unsigned int getLeftGlassCount(){return _leftGlassCount;}
    
    void refleshLeftGlassSprites();
};


#endif /* HelloWorldScene_hpp */
