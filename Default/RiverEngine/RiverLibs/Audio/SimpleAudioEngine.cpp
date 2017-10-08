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
    }
    
    return _instance;
}

void SimpleAudioEngine::init()
{
    ALCdevice *device = alcOpenDevice(NULL);
    
    if(device)
    {
        ALCcontext *context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);
    }
    
    ALenum error;
    
    alGetError();
    alGenBuffers(1, &buffer);
    
    if((error = alGetError()) != AL_NO_ERROR)
    {
        printf("alGenBuffers error");
        assert(false);
        return;
    }
    
    alGetError();
    alGenSources(1, &source);
    
    if((error = alGetError()) != AL_NO_ERROR)
    {
        printf("alGenSources error");
        assert(false);
        return;
    }
    
    alSourcei(source, AL_LOOPING, AL_TRUE);
    alSourcei(source, AL_PITCH, 1.0f);
    alSourcei(source, AL_GAIN, 0.45f);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    
    FILE *fp;
    int wavChannel,wavBit,wavSize,wavFreq;
    unsigned char *data;
    
    auto fileUtil = FileUtils::getInstance();
    auto resourcePath = fileUtil->pathForResource("Assets/BreakTheCrystal", "wav");
    
    fp = fopen(resourcePath.c_str(), "rb");
    
    if(readHeaderWav(fp, &wavChannel, &wavBit, &wavSize, &wavFreq)){
        printf("No Suported Format");
        assert(false);
    }
    
    alGenBuffers(1, &buffer);
    
    data = new unsigned char[wavSize];
    fread(data,wavSize,1,fp);
    
    //バッファへのデータ登録
    if(wavChannel==1){
        if(wavBit==8){
            alBufferData(buffer, AL_FORMAT_MONO8, data, wavSize, wavFreq);
        }else{
            alBufferData(buffer, AL_FORMAT_MONO16, data, wavSize, wavFreq);
        }
    }else{
        if(wavBit==8){
            alBufferData(buffer, AL_FORMAT_STEREO8, data, wavSize, wavFreq);
        }else{
            alBufferData(buffer, AL_FORMAT_STEREO16, data, wavSize, wavFreq);
        }
    }
    
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    
    delete[] data;
    fclose(fp);
}

//参考 http://www-fps.nifs.ac.jp/ito/memo/openal02.html
int SimpleAudioEngine::readHeaderWav(FILE* fp, int *channel, int *bit, int *size, int *freq)
{
    short res16;
    int res32;
    int dataSize, chunkSize;
    short channelCnt,bitParSample,blockSize;
    int samplingRate,byteParSec;
    
    int dataPos = 0;
    int flag = 0;
    
    fread(&res32, 4, 1,fp);
    if(res32 != 0x46464952){	//"RIFF"
        return 1;	//error 1
    }
    
    //データサイズ = ファイルサイズ - 8 byte の取得
    fread(&dataSize, 4, 1, fp);
    
    //WAVEヘッダーの読み
    fread(&res32, 4, 1, fp);
    if(res32 != 0x45564157){	//"WAVE"
        return 2;	//error 2
    }
    
    while(flag != 3){
        //チャンクの読み
        fread(&res32, 4, 1, fp);
        fread(&chunkSize, 4, 1, fp);
        
        switch(res32){
            case 0x20746d66:	//"fmt "
                //format 読み込み
                //PCM種類の取得
                fread(&res16, 2, 1, fp);
                if(res16 != 1){
                    //非対応フォーマット
                    return 4;
                }
                //モノラル(1)orステレオ(2)
                fread(&channelCnt, 2, 1, fp);
                if(res16 > 2){
                    //チャンネル数間違い
                    return 5;
                }
                //サンプリングレート
                fread(&samplingRate, 4, 1, fp);
                //データ速度(byte/sec)=サンプリングレート*ブロックサイズ
                fread(&byteParSec, 4, 1, fp);
                //ブロックサイズ(byte/sample)=チャンネル数*サンプルあたりのバイト数
                fread(&blockSize, 2, 1, fp);
                //サンプルあたりのbit数(bit/sample)：8 or 16
                fread(&bitParSample, 2, 1, fp);
                
                *channel = (int)channelCnt;
                *bit = (int)bitParSample;
                *freq = samplingRate;
                
                flag += 1;
                
                break;
            case  0x61746164:	//"data"
                
                *size = chunkSize;
                
                dataPos = ftell(fp);
                
                flag += 2;
                break;
        }
        
    }
    
    //頭出し("fmt "が"data"より後にあった場合のみ動く)
    if (dataPos != ftell(fp)){
        fseek(fp,dataPos,SEEK_SET);
    }
    
    return 0;
    return 0;
}










