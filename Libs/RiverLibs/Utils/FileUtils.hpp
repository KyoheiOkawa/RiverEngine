//
//  FileUtils.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/24.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef FileUtils_hpp
#define FileUtils_hpp

#include "stdinc.h"

#define CSTR2NSSTRING(c_str) [[NSString alloc] initWithUTF8String:c_str]

struct WavFormat
{
    unsigned short format_id;
    unsigned short num_of_channels;
    unsigned int samples_per_sec;
    unsigned int byte_per_sec;
    unsigned short block_size;
    unsigned short bits_per_sample;
};

struct Wave
{
    WavFormat fmt;
    std::vector<unsigned char> data;
};

class FileUtils
{
private:
    static FileUtils* _fileUtils;
    
    FileUtils(){};
    
public:
    static FileUtils* getInstance();
    
    std::string pathForResource(const std::string fileName,const std::string fileType);
    
    std::string getStringFromFile(const std::string fileName,const std::string fileType);
    
    size_t loadBinary(const std::string fileName,const std::string fileType,std::unique_ptr<char[]> &fileData);
    
    bool loadWavFromFile(const std::string fileName,Wave& wave);
};

#endif /* FileUtils_hpp */
