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

void SimpleAudioEngine::test2()
{
    Wave wave;
    FileUtils::getInstance()->loadWavFromFile("Assets/Why", wave);
    
    const size_t pcmFreq = wave.fmt.samples_per_sec;
    
    ALuint bufferId;
    alGenBuffers(1, &bufferId);
    
    alBufferData(bufferId, AL_FORMAT_STEREO16, &wave.data[0], wave.data.size() * sizeof(unsigned char), pcmFreq);
    
    ALuint sourceId;
    alGenSources(1, &sourceId);
    
    alSourcei(sourceId, AL_BUFFER, bufferId);
    
    alSourcePlay(sourceId);
}






