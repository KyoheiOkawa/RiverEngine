//
//  SimpleAudioEngine.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/08/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef SimpleAudioEngine_hpp
#define SimpleAudioEngine_hpp

#include <stdio.h>
#include <stdlib.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <AudioToolbox/AudioToolbox.h>
#include "FileUtils.hpp"
#include <memory.h>
#include <array>
#include <thread>

class SimpleAudioEngine
{
private:
    static SimpleAudioEngine* _instance;
    
    ALCdevice* _device;
    ALCcontext* _context;
    
    SimpleAudioEngine(){}
public:
    virtual ~SimpleAudioEngine();
    static SimpleAudioEngine* getInstance();
    
    void init();
    
    void test();
    void test2();
};

#endif /* SimpleAudioEngine_hpp */
