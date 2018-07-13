//
//  JudgePocket.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/13.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef JudgePocket_hpp
#define JudgePocket_hpp

#include "river.h"

class JudgePocket : public GameObject
{
public:
    JudgePocket();
    ~JudgePocket(){}
    
    static std::shared_ptr<JudgePocket> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
};

#endif /* JudgePocket_hpp */
