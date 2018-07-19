//
//  MainUI.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/19.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef MainUI_hpp
#define MainUI_hpp

#include "river.h"

class HighScoreUI : public GameObject
{
    shared_ptr<Sprite> _wordSprite;
    shared_ptr<NumberSprite> _score;
    
public:
    HighScoreUI();
    virtual ~HighScoreUI(){};
    
    static std::shared_ptr<HighScoreUI> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
};

#endif /* MainUI_hpp */
