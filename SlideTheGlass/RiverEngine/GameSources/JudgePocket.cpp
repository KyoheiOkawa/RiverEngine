//
//  JudgePocket.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/13.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "JudgePocket.hpp"

JudgePocket::JudgePocket()
{
    
}

std::shared_ptr<JudgePocket> create()
{
    shared_ptr<JudgePocket> ret(new JudgePocket());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool JudgePocket::init()
{
    return true;
}

void JudgePocket::update()
{
    
}

void JudgePocket::draw()
{
    
}
