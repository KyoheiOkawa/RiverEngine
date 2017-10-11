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

class SimpleAudioEngine
{
private:
    static SimpleAudioEngine* _instance;
    
    ALuint buffer;
    ALuint source;
    
    SimpleAudioEngine(){}
public:
    static SimpleAudioEngine* getInstance();
    
    void init();
    
private:
    int readHeaderWav(FILE* fp,int *channel, int *bit,int *size, int* freq);
};

#endif /* SimpleAudioEngine_hpp */
