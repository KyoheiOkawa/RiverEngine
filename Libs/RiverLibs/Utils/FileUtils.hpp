//
//  FileUtils.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/24.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef FileUtils_hpp
#define FileUtils_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>

#define CSTR2NSSTRING(c_str) [[NSString alloc] initWithUTF8String:c_str]

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
};

#endif /* FileUtils_hpp */
