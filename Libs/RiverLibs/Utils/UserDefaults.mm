//
//  UserDefaults.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/04/07.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "UserDefaults.hpp"

UserDefaults* UserDefaults::_userDefaults = nullptr;

UserDefaults* UserDefaults::getInstance()
{
    if(_userDefaults == nullptr)
    {
        _userDefaults = new UserDefaults();
    }
    
    return _userDefaults;
}

void UserDefaults::setInt(const int i,const std::string key)
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setInteger:i forKey:CSTR2NSSTRING(key.c_str())];
    [ud synchronize];
}

int UserDefaults::getInt(const std::string key)
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    return (int)[ud integerForKey:CSTR2NSSTRING(key.c_str())];
}

void UserDefaults::setFloat(const float f, const std::string key)
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setFloat:f forKey:CSTR2NSSTRING(key.c_str())];
    [ud synchronize];
}

float UserDefaults::getFloat(const std::string key)
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    return [ud floatForKey:CSTR2NSSTRING(key.c_str())];
}

void UserDefaults::setBool(const bool b, const std::string key)
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setBool:b forKey:CSTR2NSSTRING(key.c_str())];
    [ud synchronize];
}

bool UserDefaults::getBool(const std::string key)
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    return [ud boolForKey:CSTR2NSSTRING(key.c_str())];
}

void UserDefaults::setString(const std::string str, const std::string key)
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:CSTR2NSSTRING(str.c_str()) forKey:CSTR2NSSTRING(key.c_str())];
    [ud synchronize];
}

std::string UserDefaults::getString(const std::string key)
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSString *str = [ud stringForKey:CSTR2NSSTRING(key.c_str())];
    
    if(str)
        return [str UTF8String];
    
    return "";
}

void UserDefaults::resetAll()
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSDictionary *dic = [ud dictionaryRepresentation];
    for(id key in dic)
        [ud removeObjectForKey:key];
    
    [ud synchronize];
}
