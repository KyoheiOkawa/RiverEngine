//
//  GLProgramState.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/17.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "GLProgramState.hpp"

VertexAttribValue::VertexAttribValue()
: _vertexAttrib(nullptr)
,_enabled(false)
{
    
}

VertexAttribValue::VertexAttribValue(VertexAttrib *vertexAttrib)
: _vertexAttrib(vertexAttrib)
,_enabled(false)
{
    
}

void VertexAttribValue::apply()
{
    if(_enabled){
        glVertexAttribPointer(_vertexAttrib->index,
                              _value.pointer.size,
                              _value.pointer.type,
                              _value.pointer.normalized,
                              _value.pointer.stride,
                              _value.pointer.pointer);
    }
}

void VertexAttribValue::setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer)
{
    _value.pointer.size = size;
    _value.pointer.type = type;
    _value.pointer.normalized = normalized;
    _value.pointer.stride = stride;
    _value.pointer.pointer = pointer;
    _enabled = true;
}

GLProgramState::GLProgramState()
{
    
}

GLProgramState::~GLProgramState()
{
    
}

GLProgramState* GLProgramState::createWithGLProgram(GLProgram* program)
{
    auto ret = new (std::nothrow) GLProgramState();
    
    if(ret)
    {
        ret->_program = program;
    }
    
    return ret;
}

void GLProgramState::enableDefaultVertexAttribArray()
{
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
}

void GLProgramState::applyAttrib()
{
    //glVertexAttribPointer(ptr->index, ptr->size, ptr->type, ptr->normalized, ptr->stride, ptr->ptr);
    for(auto attrib : _vertexAttribValues){
        attrib->apply();
    }
}
