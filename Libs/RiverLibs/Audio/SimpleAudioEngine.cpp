//
//  SimpleAudioEngine.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/08/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "SimpleAudioEngine.hpp"

std::unique_ptr<SimpleAudioEngine> SimpleAudioEngine::_instance = nullptr;

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    if(_instance == nullptr) {
        _instance.reset(new SimpleAudioEngine());
        _instance->init();
    }
    
    return _instance.get();
}

SimpleAudioEngine::~SimpleAudioEngine()
{
    deleteSourceBuffer(_bgmMap);
    deleteSourceBuffer(_seMap);
    
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(_context);
    alcCloseDevice(_device);
    
    _context = nullptr;
    _device = nullptr;
}

void SimpleAudioEngine::deleteSourceBuffer(std::map<std::string,SoundItem>& map)
{
    for(auto item : map)
    {
        for(ALuint source : item.second.sourceIDs)
        {
            alSourcei(source, AL_BUFFER, 0);
            alDeleteSources(1, &source);
        }
        
        alDeleteBuffers(1, &item.second.bufferID);
    }
}
SoundItem* SimpleAudioEngine::registerSoundItem(const std::string soundName,const std::string soundKey, std::map<std::string, SoundItem> &soundMap)
{
    if(findSoundItem(soundKey, soundMap)!=nullptr)
        return nullptr;
    
    Wave wave;
    bool result = FileUtils::getInstance()->loadWavFromFile(soundName, wave);
    
    assert(result);
    
    SoundItem item;
    item.wavFormat = wave.fmt;
    
    alGenBuffers(1, &item.bufferID);
    
    switch (wave.fmt.num_of_channels)
    {
        case 1:
        switch (wave.fmt.bits_per_sample)
        {
            case 8:
                alBufferData(item.bufferID, AL_FORMAT_MONO8, &wave.data[0], (ALsizei)(wave.data.size() * sizeof(unsigned char)), (ALsizei)(wave.fmt.samples_per_sec));
                break;
            case 16:
                alBufferData(item.bufferID, AL_FORMAT_MONO16, &wave.data[0], (ALsizei)(wave.data.size() * sizeof(unsigned char)), (ALsizei)(wave.fmt.samples_per_sec));
                break;
        }
            break;
        case 2:
        switch (wave.fmt.bits_per_sample)
        {
            case 8:
                alBufferData(item.bufferID, AL_FORMAT_STEREO8, &wave.data[0], (ALsizei)(wave.data.size() * sizeof(unsigned char)), (ALsizei)(wave.fmt.samples_per_sec));
                break;
            case 16:
                alBufferData(item.bufferID, AL_FORMAT_STEREO16, &wave.data[0], (ALsizei)(wave.data.size() * sizeof(unsigned char)), (ALsizei)(wave.fmt.samples_per_sec));
                break;
        }
            break;
    }
    
    soundMap[soundKey] = item;
    
    return &soundMap[soundKey];
}

SoundItem* SimpleAudioEngine::findSoundItem(const std::string soundKey, std::map<std::string, SoundItem> &soundMap)
{
    auto it = soundMap.find(soundKey);
    if(it != soundMap.end())
        return &it->second;
    
    return nullptr;
}

void SimpleAudioEngine::init()
{
    _device = alcOpenDevice(nullptr);
    _context = alcCreateContext(_device, nullptr);
    alcMakeContextCurrent(_context);
}

ALint SimpleAudioEngine::getBgmSourceState(const std::string soundKey)
{
    auto item = findSoundItem(soundKey, _bgmMap);
    if(item == nullptr)
        return AL_NONE;
    
    ALint state;
    alGetSourcei(item->sourceIDs[0], AL_SOURCE_STATE, &state);
    
    return state;
}

void SimpleAudioEngine::registerBgm(const std::string soundName, const std::string soundKey)
{
    auto item = registerSoundItem(soundName, soundKey, _bgmMap);
    if(item == nullptr)
        return;
    
    alGenSources(1, &item->sourceIDs[0]);
    alSourcei(item->sourceIDs[0], AL_BUFFER, item->bufferID);
}

void SimpleAudioEngine::startBgm(const std::string soundKey,const ALfloat volume,const ALint loop)
{
    SoundItem* item = findSoundItem(soundKey, _bgmMap);
    assert(item);
    
    alSourcei(item->sourceIDs[0],AL_LOOPING, loop);
    alSourcef(item->sourceIDs[0], AL_GAIN, volume);
    alSourcePlay(item->sourceIDs[0]);
}

void SimpleAudioEngine::pauseBgm(const std::string soundKey)
{
    SoundItem* item = findSoundItem(soundKey, _bgmMap);
    assert(item);
    
    alSourcePause(item->sourceIDs[0]);
}

void SimpleAudioEngine::stopBgm(const std::string soundKey)
{
    SoundItem* item = findSoundItem(soundKey, _bgmMap);
    assert(item);
    
    if(getBgmSourceState(soundKey) != AL_PLAYING)
        return;
    
    alSourceStop(item->sourceIDs[0]);
}

void SimpleAudioEngine::registerSe(const std::string soundName, const std::string soundKey)
{
    auto item = registerSoundItem(soundName, soundKey, _seMap);
    if(item == nullptr)
        return;
    
    for(int i = 0; i < MAX_SE_SOURCE; i++)
    {
        alGenSources(1, &item->sourceIDs[i]);
        alSourcei(item->sourceIDs[i], AL_BUFFER, item->bufferID);
    }
    
}

bool SimpleAudioEngine::startSe(const std::string soundKey, const ALfloat volume)
{
    SoundItem* item = findSoundItem(soundKey, _seMap);
    assert(item);
    
    ALint playSource = -1;
    for(int i = 0; i < MAX_SE_SOURCE; i++)
    {
        ALint state;
        alGetSourcei(item->sourceIDs[i], AL_SOURCE_STATE, &state);
        
        if(state != AL_PLAYING)
        {
            playSource = i;
            break;
        }
    }
    
    if(playSource == -1)
        return false;
    
    alSourcei(item->sourceIDs[playSource], AL_GAIN, volume);
    alSourcePlay(item->sourceIDs[playSource]);
    
    return true;
}






