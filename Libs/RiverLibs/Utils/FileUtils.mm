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

std::string FileUtils::pathForResource(std::string fileName, std::string fileType)
{
    NSString* nFileName = [NSString stringWithUTF8String:fileName.c_str()];
    NSString* nFileType = [NSString stringWithUTF8String:fileType.c_str()];
    
    NSString* filePath = [[NSBundle mainBundle]pathForResource:nFileName ofType:nFileType];
    
    assert(filePath);
    
    std::string ret = [filePath UTF8String];
    
    return ret;
}

std::string FileUtils::getStringFromFile(std::string fileName, std::string fileType)
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
