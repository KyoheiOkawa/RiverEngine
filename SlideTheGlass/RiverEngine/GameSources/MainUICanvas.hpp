//
//  MainUICanvas.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/24.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef MainUICanvas_hpp
#define MainUICanvas_hpp

#include "river.h"

class MainUICanvas : public GameObject
{
    shared_ptr<Sprite> _rankButton;
    
    bool isInPoint(Vector2 point,Vector2 otherPoint,Vector2 otherSize);
public:
    MainUICanvas();
    virtual ~MainUICanvas(){}
    
    static shared_ptr<MainUICanvas> create();
    
    virtual bool init()override;
    virtual void update()override;
    virtual void draw()override;
    virtual void onScreenTouched(TouchInfo& info)override;
};

#endif /* MainUICanvas_hpp */
