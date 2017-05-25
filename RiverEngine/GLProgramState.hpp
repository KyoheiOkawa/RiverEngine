//
//  GLProgramState.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/17.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef GLProgramState_hpp
#define GLProgramState_hpp

#include <stdio.h>
#include "GLProgram.hpp"
#include <vector>

class VertexAttribValue
{
public:
    VertexAttribValue(VertexAttrib *vertexAttrib);
    
    VertexAttribValue();
    
    ~VertexAttribValue(){}
    
    void setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei sttride, GLvoid *pointer);
    
    void apply();
    
protected:
    VertexAttrib* _vertexAttrib;
    bool _enabled;
    
    union U{
        struct{
            GLint size;
            GLenum type;
            GLboolean normalized;
            GLsizei stride;
            GLvoid *pointer;
        } pointer;
        
        U(){memset(this, 0, sizeof(*this));}
        ~U(){}
        U& operator=(const U& other){
            memcpy(this,&other,sizeof(*this));
            return *this;
        }
    } _value;
};

class GLProgramState{
protected:
    GLProgram* _program;
    
    std::vector<VertexAttribValue*> _vertexAttribValues;
    
    GLProgramState();
    ~GLProgramState();
    
public:
    static GLProgramState* createWithGLProgram(GLProgram* program);
    
    void use(){
        _program->use();
    }
    
    void enableDefaultVertexAttribArray();
    
    void applyAttrib();
    
    void setAttrib(VertexAttribValue* value){
        _vertexAttribValues.push_back(value);
    }
};

#endif /* GLProgramState_hpp */
