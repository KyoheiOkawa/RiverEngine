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

#define MAX_SE_SOURCE 10

struct SoundItem
{
    WavFormat wavFormat;
    ALuint bufferID;
    array<ALuint, MAX_SE_SOURCE> sourceIDs;
};

class SimpleAudioEngine
{
private:
    static std::unique_ptr<SimpleAudioEngine> _instance;
    
    ALCdevice* _device;
    ALCcontext* _context;
    
    std::map<std::string,SoundItem> _bgmMap;
    std::map<std::string,SoundItem> _seMap;
    
    SimpleAudioEngine(){}
    void deleteSourceBuffer(std::map<std::string,SoundItem>& map);
    
    SoundItem* registerSoundItem(const std::string soundName,const std::string soundKey,std::map<std::string,SoundItem>& soundMap);
    
    SoundItem* findSoundItem(const std::string soundKey,std::map<std::string,SoundItem>& soundMap);
public:
    virtual ~SimpleAudioEngine();
    static SimpleAudioEngine* getInstance();
    
    void init();
    
    ALint getBgmSourceState(const std::string soundKey);
    
    void registerBgm(const std::string soundName,const std::string soundKey);
    void startBgm(const std::string soundKey,const ALfloat volume,const ALint loop);
    void pauseBgm(const std::string soundKey);
    void stopBgm(const std::string soundKey);
    
    void registerSe(const std::string soundName,const std::string soundKey);
    bool startSe(const std::string soundKey,const ALfloat volume);
};

#endif /* SimpleAudioEngine_hpp */
