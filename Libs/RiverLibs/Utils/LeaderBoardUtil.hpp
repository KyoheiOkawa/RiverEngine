//
//  LeaderBoardUtil.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/24.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef LeaderBoardUtil_hpp
#define LeaderBoardUtil_hpp

#include "river.h"

class LeaderBoardUtil
{
private:
    static LeaderBoardUtil* _instance;
    
    LeaderBoardUtil(){}
    
public:
    static LeaderBoardUtil* getInstance();
    
    void showLeaderBoard();
    void sendScore(int score);
};

#endif /* LeaderBoardUtil_hpp */
