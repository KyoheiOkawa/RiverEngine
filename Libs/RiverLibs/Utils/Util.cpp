//
//  Util.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/10.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "stdinc.h"
#include "Util.hpp"

namespace MyUtil
{
    int getDigit(int number)
    {
        return std::to_string(number).length();
    }
    
    std::vector<int> extractTotalDigitsSpotCount(int number,int digit)
    {
        vector<int> result;
        
        for (int i = 0; i < digit; i++)
        {
            if (number == 0)
            {
                result.push_back(0);
                continue;
            }
            
            result.push_back(number % 10);
            number /= 10;
        }
        
        return result;
    }
}
