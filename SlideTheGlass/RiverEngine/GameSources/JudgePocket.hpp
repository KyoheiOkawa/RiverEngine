//
//  JudgePocket.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/13.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef JudgePocket_hpp
#define JudgePocket_hpp

#include "river.h"

//テーブル４隅の位置x,z
//左奥　-0.5f -1.1f
//右奥  0.5f -1.1f
//左前　-0.5f -1.055f
//右前　0.5f 1.055f

class JudgePocket : public GameObject
{
    const float _defaultRadius;
    const float _hightScoreRadius;
    float _radius;
    const float _minRadius;
    Color4 _color;
    const Color4 _defaultColor;
    const Color4 _highScoreColor;
    const Color4 _onColor;
    const float _randomMoveSpeedSec;
    
    weak_ptr<GameObject> _glass;
    //グラスの下の部分の半径
    const float _glassRadius;
    ///グラスが円の中にあるとき色変更
    void updateCircleColor();
public:
    JudgePocket();
    ~JudgePocket(){}
    
    static std::shared_ptr<JudgePocket> create();
    
    virtual bool init() override;
    virtual void update() override;
    virtual void draw() override;
    
    ///ランダムなところに円を動かす
    void moveRandom();
    ///渡された値が円の中に入っているかどうか
    bool isInPocket(Vector3 pos);
    ///ハイスコアポケットの中に渡された値が入っているかどうか
    bool isInHighScorePocket(Vector3 pos);
    
    void reset();
};

#endif /* JudgePocket_hpp */
