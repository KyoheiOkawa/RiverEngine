//
//  Random.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/17.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Random.hpp"

Random* Random::_instance = nullptr;

Random* Random::getInstance()
{
    if(_instance == nullptr)
    {
        _instance = new Random();
    }
    
    return _instance;
}

void Random::init()
{
    _mt.seed(_rDevice());
}

uint32_t Random::getRandom()
{
    return _mt();
}

int Random::range(int min, int max)
{
    uniform_int_distribution<int> rand(min,max);
    return rand(_mt);
}

float Random::range(float min, float max)
{
    uniform_real_distribution<float> rand(min,max);
    return rand(_mt);
}
