//
//  Random.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/17.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Random_hpp
#define Random_hpp

#include "stdinc.h"

class Random
{
    Random(){}
    static Random* _instance;
    
    random_device _rDevice;
    mt19937 _mt;
public:
    void init();
    static Random* getInstance();
    
    uint32_t getRandom();
    
    int range(int min, int max);
    float range(float min, float max);
};

#endif /* Random_hpp */
