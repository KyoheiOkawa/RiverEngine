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















