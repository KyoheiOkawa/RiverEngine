//
//  Application.h
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Application_h
#define Application_h

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include "GLProgram.hpp"

enum TouchType
{
    BEGAN,
    MOVED,
    ENDED
};

struct TouchInfo
{
    TouchType type;
    float posX,posY;
};

/**
 *@class Application
 *@brief アプリケーションクラス（シングルトン）
 */
class Application{
private:
    ///コンストラクタ
    Application();
    
    ///自分自信へのポインタ
    static Application* _application;

    ///View(レンダリングターゲット）の幅
    int _surface_width;
    ///View（レンダリングターゲット）の高さ
    int _surface_height;
    
    void* _glesView;
    
    void* _viewController;
    ///１フレーム更新にかかった時間
    float _deltaTime;
 
public:
    static Application* getInstance();
    
    int getSurfaceWidth(){
        return _surface_width;
    }
    
    int getSurfaceHeight(){
        return _surface_height;
    }
    
    void* getGLESView(){
        return _glesView;
    }
    
    void* getViewController(){
        return _viewController;
    }
    
    float getDeltaTime(){
        if(_deltaTime > 1.0f){
            return 0;
        }
        
        return _deltaTime;
    }

    void setSurfaceWidth(int width){
        _surface_width = width;
    }
    
    void setSurfaceHeight(int height){
        _surface_height = height;
    }
    
    void setGLESView(void* view){
        _glesView = view;
    }
    
    void setViewController(void* controller){
        _viewController = controller;
    }
    
    void setDeltaTIme(float delta){
        _deltaTime = delta;
    }
    
    ///初期化関数
    void initialize();
    ///非同期処理
    void async();
    ///サーフェイスサイズ変更関数
    void resized();
    ///アップデート
    void update();
    ///レンダリング関数
    void rendering();
    ///解放処理
    void destroy();
    
    void onScreenTouched(TouchInfo& touchInfo);
};

#endif
