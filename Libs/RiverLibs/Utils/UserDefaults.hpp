//
//  UserDefaults.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/04/07.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef UserDefaults_hpp
#define UserDefaults_hpp

#include "stdinc.h"

class UserDefaults
{
private:
    static UserDefaults* _userDefaults;
    UserDefaults(){};
    
public:
    static UserDefaults* getInstance();
    
    void setInt(const int i,const std::string key);
    int getInt(const std::string key);
    
    void setFloat(const float f, const std::string key);
    float getFloat(const std::string key);
    
    void setBool(const bool b, const std::string key);
    bool getBool(const std::string key);
    
    void setString(const std::string str, const std::string key);
    std::string getString(const std::string key);
    
    void resetAll();
};

#endif /* UserDefaults_hpp */
