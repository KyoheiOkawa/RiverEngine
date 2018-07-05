//
//  Lerp.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/05.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Lerp_hpp
#define Lerp_hpp

#include "MathMacro.h"
#include "stdinc.h"

struct Lerp{
    enum rate{
        Linear,    //1次関数（線形）
        Easein,    //2次関数ゆっくり上昇
        EaseOut,//2次関数最後がゆっくり
        Cube,    //3次関数
        Cos        //コサイン
    };
    //--------------------------------------------------------------------------------------
    /*!
     @brief    T型の補間計算を行う
     @tparam    T    計算する型
     @param[in]    Start    開始値
     @param[in]    End    終了値
     @param[in]    StartTime    開始時間
     @param[in]    EndTime    終了時間
     @param[in]    NowTime    現在の時間
     @param[in]    r    計算方法
     @return    T型の計算結果
     */
    //--------------------------------------------------------------------------------------
    template<typename T>
    static T CalculateLerp(const T &Start, const T &End,
                           float StartTime, float EndTime, float NowTime, rate r){
        float t = (NowTime - StartTime) / (EndTime - StartTime);
        if (t < 0.0f){
            t = 0;
        }
        if (t > 1.0f){
            t = 1.0f;
        }
        float cal_rate = t;   // 1次関数補間値に変換(デフォルト)
        switch (r){
            case Linear:
                cal_rate = t;
                break;
            case Easein:
                cal_rate = t * t;
                break;
            case EaseOut:
                cal_rate = t * (2.0f - t);
                break;
            case Cube:
                cal_rate = t * t * (3.0f - 2.0f * t);
                break;
            case Cos:
                cal_rate = (1.0f - cos(t * PI)) / 2.0f;
                break;
            default:
                break;
        }
        return Start * (1.0f - cal_rate) + End * cal_rate;
    }
};

#endif /* Lerp_hpp */
