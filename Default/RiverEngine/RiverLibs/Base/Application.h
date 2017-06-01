//
//  Application.h
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include "GLProgram.hpp"
#include "GLProgramState.hpp"

class Application{
private:
    Application();
    
    static Application* _application;

    ///View(レンダリングターゲット）の幅
    int _surface_width;
    ///View（レンダリングターゲット）の高さ
    int _surface_height;
    
    void* _glesView;
    
    void* _viewController;
    
    float _deltaTime;
    
    GLProgram* _program;

    GLfloat* _position;
 
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
};
