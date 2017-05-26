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

class FileUtils
{
private:
    static FileUtils* _fileUtils;
    
    FileUtils(){};
    
public:
    static FileUtils* getInstance();
    
    std::string pathForResource(std::string fileName,std::string fileType);
    
    std::string getStringFromFile(std::string fileName,std::string fileType);
};

#endif /* FileUtils_hpp */
