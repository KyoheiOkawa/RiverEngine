//
//  LeaderBoardUtil.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/24.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "LeaderBoardUtil.hpp"
#import <GameKit/GameKit.h>
#import "ViewController.h"

LeaderBoardUtil* LeaderBoardUtil::_instance = nullptr;

LeaderBoardUtil* LeaderBoardUtil::getInstance()
{
    if(_instance == nullptr)
    {
        _instance = new LeaderBoardUtil();
    }
    
    return _instance;
}

void LeaderBoardUtil::showLeaderBoard()
{
    GKGameCenterViewController *gcView = [GKGameCenterViewController new];
    if(gcView != nil)
    {
        ViewController* view = (__bridge ViewController*)Application::getInstance()->getViewController();
        gcView.gameCenterDelegate = view;
        gcView.viewState = GKGameCenterViewControllerStateLeaderboards;
        [view presentViewController:gcView animated:YES completion:nil];
    }
}

void LeaderBoardUtil::sendScore(int score)
{
    GKScore* gkScore = [[GKScore alloc] initWithLeaderboardIdentifier:@"stl_rank"];
    gkScore.value = (int64_t)score;
    [GKScore reportScores:@[gkScore] withCompletionHandler:^(NSError * error)
    {
        if(error)
            printf("can't send score");
    }];
}
