//
//  GLProgram.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "GLProgram.hpp"
#include "FileUtils.hpp"
#include <assert.h>

const char* GLProgram::ATTRIBUTE_NAME_POSITION = "attr_pos";

GLProgram::GLProgram():
_program(0),
_vertShader(0),
_fragShader(0)
{
    
}

GLProgram::~GLProgram()
{
    clearShaser();
    
    if(_program)
    {
        glDeleteProgram(_program);
    }
}

void GLProgram::clearShaser()
{
    if(_vertShader)
    {
        glDeleteShader(_vertShader);
    }
    
    if(_fragShader)
    {
        glDeleteShader(_fragShader);
    }
    
    _vertShader = 0;
    _fragShader = 0;
}

GLuint GLProgram::loadWithByteArray(const char* shader_source, const GLenum GL_XXXX_SHADER)
{
    const GLint shader = glCreateShader(GL_XXXX_SHADER);
    assert(glGetError() == GL_NO_ERROR);
    
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    
    //コンパイルエラーチェック
    checkCompileError(shader);
    
    return shader;
}

GLProgram* GLProgram::createWithByteArray(const char* vertex_shader_source, const char* fragment_shader_source)
{
    auto ret = new (std::nothrow) GLProgram;
    
    if(ret)
    {
        const GLuint _vertShader = loadWithByteArray(vertex_shader_source, GL_VERTEX_SHADER);
        const GLuint _fragShader = loadWithByteArray(fragment_shader_source, GL_FRAGMENT_SHADER);
        
        const GLuint program = glCreateProgram();
        assert(glGetError() == GL_NO_ERROR);
        assert(program != 0);
        
        glAttachShader(program, _vertShader);
        glAttachShader(program, _fragShader);
        assert(glGetError() == GL_NO_ERROR);
        
        glLinkProgram(program);
        
        //リンクエラーチェック
        checkLinkError(program);
        
        ret->_program = program;
        ret->bindDefaultVertexAttribs();
        
        return ret;
    }
    
    delete ret;
    
    return nullptr;
}

GLProgram* GLProgram::createWithFile(const std::string& vShaderFileName, const std::string& fShaderFileName)
{
    auto fileUtils = FileUtils::getInstance();
    
    std::string vstr = fileUtils->getStringFromFile(vShaderFileName, "vsh").c_str();
    std::string fstr = fileUtils->getStringFromFile(fShaderFileName, "fsh").c_str();
    
    GLchar *vertex_shader_source = new GLchar[vstr.size() + 1];
    
    GLchar *fragment_shader_source = new GLchar[fstr.size() + 1];
    
    std::strcpy(vertex_shader_source, vstr.c_str());
    std::strcpy(fragment_shader_source, fstr.c_str());
    
    auto ret = GLProgram::createWithByteArray(vertex_shader_source, fragment_shader_source);
    
    delete[] vertex_shader_source;
    delete[] fragment_shader_source;
    
    if(ret)
    { 
        return ret;
    }
    
    delete ret;
    
    return nullptr;
}

void GLProgram::use()
{
    glUseProgram(_program);
    assert(glGetError() == GL_NO_ERROR);
}

void GLProgram::checkCompileError(const GLint shader)
{
    GLint compileSuccess = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
    if(compileSuccess == GL_FALSE){
        GLint infoLen = 0;
        
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1){
            GLchar *message = (GLchar*) calloc(infoLen, sizeof(GLchar));
            glGetShaderInfoLog(shader, infoLen, NULL, message);
            printf("%s\n",message);
            free((void*)message);
        }
        else{
            printf("compile error not info...");
        }
    }
    
    assert(compileSuccess == GL_TRUE);
}

void GLProgram::checkLinkError(const GLuint program)
{
    GLint linkSuccess = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
    if(linkSuccess == GL_FALSE){
        GLint infoLen = 0;
        
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1){
            GLchar *message = (GLchar*) calloc(infoLen, sizeof(GLchar));
            glGetProgramInfoLog(program, infoLen, NULL, message);
            printf("%s\n",message);
            free((void*)message);
        }
    }
    assert(linkSuccess == GL_TRUE);
}

void GLProgram::bindDefaultVertexAttribs()
{
    static const struct{
        const char *attributeName;
        int location;
    } attribute_locations[] =
    {
        {GLProgram::ATTRIBUTE_NAME_POSITION,GLProgram::VERTEX_ATTRIB_POSITION}
    };
    
    const int size = sizeof(attribute_locations) / sizeof(attribute_locations[0]);
    
    for(int i = 0; i < size; i++){
        glBindAttribLocation(_program, attribute_locations[i].location, attribute_locations[i].attributeName);
    }
}
