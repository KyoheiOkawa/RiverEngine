//
//  GLProgram.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef GLProgram_hpp
#define GLProgram_hpp

#include "stdinc.h"

struct VertexAttrib
{
    ///０から始まるattributeのインデックス
    GLuint index;
    ///attributeデータの数（範囲は０から４）
    GLint size;
    ///attrubuteのデータのタイプ(ex GL_FLOAT,GL_UNSIGNED_BYTE...)
    GLenum type;
    ///バーテックスシェーダーの名前(std::string)
    std::string name;
};

class GLProgram{
protected:
    GLuint _program;
    GLuint _vertShader;
    GLuint _fragShader;
    
    static void checkCompileError(const GLint shader);
    static void checkLinkError(const GLuint program);
    void clearShaser();
    
    GLProgram();
    virtual ~GLProgram();
public:
    enum{
        VERTEX_ATTRIB_POSITION
    };
    
    static const char* ATTRIBUTE_NAME_POSITION;
    
    
    static GLProgram* createWithByteArray(const char* vertex_shader_source,
                               const char* fragment_shader_source);
    
    static GLProgram* createWithFile(const std::string& vShaderFilename,const std::string& fShaderFilename);
    
    static GLuint loadWithByteArray(const char* shader_source,const GLenum GL_XXXX_SHADER);
    
    void use();
    
    GLuint& getProgram(){
        return _program;
    }
    
    GLint getAttribLocation(GLchar* name){
        auto ret = glGetAttribLocation(_program, name);
        assert(ret >= 0);
        
        return ret;
    }
    
    GLint getUnifLocation(GLchar* name){
        auto ret = glGetUniformLocation(_program, name);
        assert(ret >= 0);
        
        return ret;
    }
};

#endif /* GLProgram_hpp */
