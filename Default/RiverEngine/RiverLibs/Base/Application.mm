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
    auto fileUtils = FileUtils::getInstance();
    
    std::string vstr = fileUtils->getStringFromFile("Shaders/SimpleShader", "vsh").c_str();
    std::string fstr = fileUtils->getStringFromFile("Shaders/SimpleShader", "fsh").c_str();
    
    GLchar *vertex_shader_source = new GLchar[vstr.size() + 1];
//    "attribute mediump vec4 attr_pos;"
//    "void main(){"
//    "   gl_Position = attr_pos;"
//    "}";
    
    GLchar *fragment_shader_source = new GLchar[fstr.size() + 1];
    //    "void main(){"
    //    "   gl_FragColor = vec4(1.0,0.0,0.0,1.0);"
    //    "}";
    std::strcpy(vertex_shader_source, vstr.c_str());
    std::strcpy(fragment_shader_source, fstr.c_str());
    
    _program = GLProgram::createWithByteArray(vertex_shader_source, fragment_shader_source);
    
    //_program->getAttrPos() = glGetAttribLocation(_program->getShaderProgram(), "attr_pos");
    //assert(_program->getAttrPos() >= 0);
    
    //glUseProgram(_program->getShaderProgram());
    //assert(glGetError() == GL_NO_ERROR);
    
    _programState = GLProgramState::createWithGLProgram(_program);
    
    _programState->use();
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
}

void Application::rendering()
{
    glClearColor(0.0913f, 0.0913f, 0.436f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //glEnableVertexAttribArray(0);
    _programState->enableDefaultVertexAttribArray();
    
    const GLfloat position[] = {
        0.0f,1.0f,
        1.0f,-1.0f,
        -1.0f,-1.0f
    };
    
    VertexAttrib va = {
        GLProgram::VERTEX_ATTRIB_POSITION,
        2,
        GL_FLOAT,
        "attr_pos"
    };
    
    VertexAttribValue *attrValue = new VertexAttribValue(&va);
    attrValue->setPointer(2, GL_FLOAT, false, 0, (GLvoid*)position);
    _programState->setAttrib(attrValue);
    
    //glVertexAttribPointer(_program->getAttrPos(), 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
    //_program->applyAttrib((GLvoid*)position);
    _programState->applyAttrib();
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    ES20_postFrontBuffer(this);
}

void Application::destroy()
{

}
