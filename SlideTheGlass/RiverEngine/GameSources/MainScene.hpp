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
    }
    void resetScore()
    {
        _nowScore = 0;
        _scoreNumber->changeNumber(_nowScore);
    }
    unsigned int getScore(){return _nowScore;}
};


#endif /* HelloWorldScene_hpp */
