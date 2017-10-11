//
//  SimpleAudioEngine.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/08/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "SimpleAudioEngine.hpp"

SimpleAudioEngine* SimpleAudioEngine::_instance = nullptr;

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    if(_instance == nullptr) {
        _instance = new SimpleAudioEngine();
        _instance->init();
    }
    
    return _instance;
}

SimpleAudioEngine::~SimpleAudioEngine()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(_context);
    alcCloseDevice(_device);
    
    _context = nullptr;
    _device = nullptr;
}

void SimpleAudioEngine::init()
{
    _device = alcOpenDevice(nullptr);
    _context = alcCreateContext(_device, nullptr);
    alcMakeContextCurrent(_context);
}

void SimpleAudioEngine::test()
{
    const size_t pcmFreq = 44100;
    const float keyFreq = 440.0f;
    
    std::array<ALshort, pcmFreq> pcmData;
    for(size_t i = 0; i < pcmData.size(); ++i)
    {
        pcmData[i] = std::sin(keyFreq * M_PI * 2.0f * i / pcmFreq) * std::numeric_limits<ALshort>::max();
    }
    
    ALuint bufferId;
    alGenBuffers(1, &bufferId);
    
    alBufferData(bufferId, AL_FORMAT_MONO16, &pcmData[0], pcmData.size() * sizeof(ALshort), pcmFreq);
    
    ALuint sourceId;
    alGenSources(1, &sourceId);
    
    alSourcei(sourceId, AL_BUFFER, bufferId);
    
    alSourcePlay(sourceId);
    
    std::this_thread::sleep_for(std::chrono
                                ::seconds(1));
    
    alSourcei(sourceId, AL_BUFFER, 0);
    alDeleteSources(1, &sourceId);
    alDeleteBuffers(1, &bufferId);
}








