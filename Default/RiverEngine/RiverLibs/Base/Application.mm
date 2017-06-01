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
//    auto fileUtils = FileUtils::getInstance();
//    
//    std::string vstr = fileUtils->getStringFromFile("Shaders/SimpleShader", "vsh").c_str();
//    std::string fstr = fileUtils->getStringFromFile("Shaders/SimpleShader", "fsh").c_str();
//    
//    GLchar *vertex_shader_source = new GLchar[vstr.size() + 1];
//    
//    GLchar *fragment_shader_source = new GLchar[fstr.size() + 1];
//
//    std::strcpy(vertex_shader_source, vstr.c_str());
//    std::strcpy(fragment_shader_source, fstr.c_str());
//    
//    _program = GLProgram::createWithByteArray(vertex_shader_source, fragment_shader_source);
//    
//    delete[] vertex_shader_source;
//    delete[] fragment_shader_source;
//    
//    _program->use();
//    
//    static GLfloat position[] = {
//        0.0f,1.0f,
//        1.0f,-1.0f,
//        -1.0f,-1.0f
//    };
//    
//    _position = position;
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
    printf("DeltaTime:%f\n",_deltaTime);
    printf("FPS:%f\n",1.0f/_deltaTime);
    
    Director::getInstance()->updateScene();
}

void Application::rendering()
{
    glClearColor(0.0913f, 0.0913f, 0.436f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
//    glEnableVertexAttribArray(0);
//    
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)_position);
//    
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    
    Director::getInstance()->drawScene();
    
    ES20_postFrontBuffer(this);
}

void Application::destroy()
{

}
