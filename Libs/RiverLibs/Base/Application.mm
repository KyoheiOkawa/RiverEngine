//
//  Application.m
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "support_gl.h"
#include "Director.hpp"
#include "Scene.hpp"
#include "FileUtils.hpp"

Application* Application::_application = nullptr;

Application::Application(){
    
}

Application* Application::getInstance()
{
    if(_application == nullptr){
        _application = new Application();
    }
    
    return _application;
}

void Application::initialize()
{

}

void Application::async()
{
    
}

void Application::resized()
{
    glViewport(0, 0, _surface_width, _surface_height);
}

void Application::update()
{
//    printf("DeltaTime:%f\n",_deltaTime);
//    printf("FPS:%f\n",1.0f/_deltaTime);
    
    Director::getInstance()->updateScene();
}

void Application::rendering()
{
    glClearColor(0.0913f, 0.0913f, 0.436f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Director::getInstance()->drawScene();
    
    ES20_postFrontBuffer(this);
}

void Application::destroy()
{
    
}

void Application::onScreenTouched(TouchInfo& touchInfo)
{
    Director::getInstance()->onScreenTouched(touchInfo);
}
