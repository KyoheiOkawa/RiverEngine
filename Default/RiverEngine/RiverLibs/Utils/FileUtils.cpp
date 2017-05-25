//
//  FileUtils.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/24.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "FileUtils.hpp"

FileUtils* FileUtils::_fileUtils = nullptr;

FileUtils* FileUtils::getInstance()
{
    if(_fileUtils == nullptr)
    {
        _fileUtils = new FileUtils();
    }
    
    return _fileUtils;
}
