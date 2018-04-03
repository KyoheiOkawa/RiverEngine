//
//  FileUtils.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/24.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "FileUtils.hpp"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iterator>

struct WavChunk
{
    char ID[4];
    int size;
};

FileUtils* FileUtils::_fileUtils = nullptr;

FileUtils* FileUtils::getInstance()
{
    if(_fileUtils == nullptr)
    {
        _fileUtils = new FileUtils();
    }
    
    return _fileUtils;
}

std::string FileUtils::pathForResource(const std::string fileName,const std::string fileType)
{
    NSString* nFileName = [NSString stringWithUTF8String:fileName.c_str()];
    NSString* nFileType = [NSString stringWithUTF8String:fileType.c_str()];
    
    NSString* filePath = [[NSBundle mainBundle]pathForResource:nFileName ofType:nFileType];
    
    assert(filePath);
    
    std::string ret = [filePath UTF8String];
    
    return ret;
}

std::string FileUtils::getStringFromFile(const std::string fileName,const std::string fileType)
{
    std::string path = pathForResource(fileName, fileType);
    
    std::ifstream ifs;
    ifs.open(path,std::ios::in);
    
    //failed open file
    assert(!ifs.fail());
    
    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);
    
    //std::cout << "string:" << str << std::endl;
    
    ifs.close();
    
    return str;
}

size_t FileUtils::loadBinary(const std::string fileName,const std::string fileType,std::unique_ptr<char[]> &fileData)
{
    std::string filePath = pathForResource(fileName, fileType);
    
    std::ifstream ifs(filePath.c_str(),std::ios::binary | std::ios::in);
    
    size_t fileSize = static_cast<size_t>(ifs.seekg(0,std::ios::end).tellg());
    ifs.seekg(0,std::ios::beg);
    
    fileData.reset(new char[fileSize]);
    
    ifs.read(fileData.get(), fileSize);
    
    ifs.close();
    
    return fileSize;
}

bool FileUtils::loadWavFromFile(const std::string fileName,Wave& wave)
{
    WavChunk chunk;
    WavFormat fmt;
    std::vector<unsigned char> data;
    char type[4];
    
    std::string filePath = pathForResource(fileName, "wav");
    
    std::ifstream ifs(filePath,std::ios::binary);
    if(!ifs)
        return false;
    
    ifs.read((char*)&chunk, 8);
    if(ifs.bad() || strncmp(chunk.ID, "RIFF", 4)!=0)
        return false;
    
    ifs.read((char*)type, 4);
    if(ifs.bad() || strncmp(type, "WAVE", 4)!=0)
        return false;
    
    try
    {
        ifs.exceptions(std::ios::badbit);
        
        while(ifs.read((char*)&chunk, sizeof(WavChunk)))
        {
            if(strncmp(chunk.ID, "fmt ", 4) == 0)
            {
                ifs.read((char*)&fmt, MIN(16, chunk.size));
                
                if(chunk.size != 16)
                    ifs.seekg(chunk.size - 16,std::ios::cur);
                
                if(fmt.format_id!=1)
                {
                    return false;
                }
            }
            else if(strncmp(chunk.ID, "data", 4)==0)
            {
                data.resize(chunk.size);
                ifs.read((char*)&data[0], data.size());
                
                break;
            }
            else
            {
                ifs.seekg(chunk.size,std::ios::cur);
            }
        }
        
        
    } catch (std::ios_base::failure& e)
    {
        return false;
    }
    
    wave.fmt = fmt;
    wave.data = data;
    
    return true;
}













