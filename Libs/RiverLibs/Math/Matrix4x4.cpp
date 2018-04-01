//
//  Matrix4x4.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/16.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "stdinc.h"
#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "MathMacro.h"

Matrix4x4::Matrix4x4()
{
    identity();
}

void Matrix4x4::identity()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i == j)
                matrix[i*4+j] = 1.0f;
            else
                matrix[i*4+j] = 0.0f;
        }
    }
}

void Matrix4x4::transpose()
{
    float temp[16];
    for(int i = 0; i < 16; i++)
        temp[i] = matrix[i];
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            matrix[i*4+j] = temp[j*4+i];
        }
    }
}

Matrix4x4 Matrix4x4::createTranslate(const float x, const float y, const float z)
{
    Matrix4x4 ret;
    
    ret.matrix[3*4+0] = x;
    ret.matrix[3*4+1] = y;
    ret.matrix[3*4+2] = z;
    
    return ret;
}

Matrix4x4 Matrix4x4::createScale(const float x,const float y, float z)
{
    Matrix4x4 ret;
    
    ret.matrix[0] = x;
    ret.matrix[5] = y;
    ret.matrix[10] = z;
    
    return ret;
}

Matrix4x4 Matrix4x4::createRotate(const Vector3 axis, const float rotate)
{
    Matrix4x4 ret;
    
    const float x = axis.x;
    const float y = axis.y;
    const float z = axis.z;
    
    const float c = cosf(Deg2Rad(rotate));
    const float s = sinf(Deg2Rad(rotate));
    {
        ret.matrix[0] = (x * x) * (1.0f - c) + c;
        ret.matrix[1] = (x * y) * (1.0f - c) - z * s;
        ret.matrix[2] = (x * z) * (1.0f - c) + y * s;
        ret.matrix[3] = 0;
    }
    {
        ret.matrix[4] = (y * x) * (1.0f - c) + z * s;
        ret.matrix[5] = (y * y) * (1.0f - c) + c;
        ret.matrix[6] = (y * z) * (1.0f - c) - x * s;
        ret.matrix[7] = 0;
    }
    {
        ret.matrix[8] = (z * x) * (1.0f - c) - y * s;
        ret.matrix[9] = (z * y) * (1.0f - c) + x * s;
        ret.matrix[10] = (z * z) * (1.0f - c) + c;
        ret.matrix[11] = 0;
    }
    {
        ret.matrix[12] = 0;
        ret.matrix[13] = 0;
        ret.matrix[14] = 0;
        ret.matrix[15] = 1;
    }
    
    return ret;
}

Matrix4x4 Matrix4x4::multiply(const Matrix4x4 a, const Matrix4x4 b)
{
    Matrix4x4 ret;
    
    for(int i = 0; i < 4; i++)
    {
        ret.matrix[i*4+0] = a.matrix[0] * b.matrix[i*4+0] + a.matrix[1*4+0] * b.matrix[i*4+1] + a.matrix[2*4+0] * b.matrix[i*4+2] + a.matrix[3*4+0] * b.matrix[i*4+3];
        
        ret.matrix[i*4+1] = a.matrix[1] * b.matrix[i*4+0] + a.matrix[1*4+1] * b.matrix[i*4+1] + a.matrix[2*4+1] * b.matrix[i*4+2] + a.matrix[3*4+1] * b.matrix[i*4+3];
        
        ret.matrix[i*4+2] = a.matrix[2] * b.matrix[i*4+0] + a.matrix[1*4+2] * b.matrix[i*4+1] + a.matrix[2*4+2] * b.matrix[i*4+2] + a.matrix[3*4+2] * b.matrix[i*4+3];
        
        ret.matrix[i*4+3] = a.matrix[3] * b.matrix[i*4+0] + a.matrix[1*4+3] * b.matrix[i*4+1] + a.matrix[2*4+3] * b.matrix[i*4+2] + a.matrix[3*4+3] * b.matrix[i*4+3];
    }
    
    return ret;
}

Matrix4x4 Matrix4x4::create2DAffine(const Vector3 pos, const Vector2 spriteSize,const Vector3 scale,const float rot, const Vector2 screenSize,const Vector3 pivot = Vector3(0.5f,0.5f,0.5f))
{
    const GLfloat surfaceAspect = (GLfloat) screenSize.x / (GLfloat) screenSize.y;
    const Matrix4x4 aspect = Matrix4x4::createScale(1, surfaceAspect, 1);
    
    const GLfloat xScale = (GLfloat)spriteSize.x / (GLfloat) screenSize.x * 2.0f;
    const GLfloat yScale = (GLfloat)spriteSize.y / (GLfloat) screenSize.x * 2.0f;
    
    const Matrix4x4 scaleMat = Matrix4x4::createScale(xScale, yScale, 0);
    
    const GLfloat vertexLeft = 0.5f + (1.0 - xScale) * 0.5f + xScale * pivot.x;
    const GLfloat vertexTop = 0.5f + (1.0f - (yScale*surfaceAspect)) * 0.5f + yScale * surfaceAspect * pivot.y;
    const GLfloat moveX = (GLfloat)pos.x / (GLfloat) screenSize.x * 2.0f;
    const GLfloat moveY = -((GLfloat)pos.y / (GLfloat) screenSize.y * 2.0f);
    
    const Matrix4x4 translate = Matrix4x4::createTranslate(-vertexLeft+moveX, vertexTop + moveY, 0);
    const Matrix4x4 rotate = Matrix4x4::createRotate(Vector3::FORWARD(), rot);
    
    Matrix4x4 ret = Matrix4x4::multiply(translate, aspect);
    ret = Matrix4x4::multiply(ret, rotate);
    ret = Matrix4x4::multiply(ret, scaleMat);
    
    return ret;
}

Matrix4x4 Matrix4x4::createLookAt(const Vector3 eye, const Vector3 look, const Vector3 up)
{
    Matrix4x4 result;
    
    Vector3 f = Vector3(look.x - eye.x,look.y - eye.y,look.z - eye.z);
    f.normalize();
    Vector3 u = up.getNormalized();
    Vector3 s = Vector3::cross(f, u);
    s.normalize();
    u = Vector3::cross(s, f);
    
    result.matrix[0] = s.x;
    result.matrix[4] = s.y;
    result.matrix[8] = s.z;
    
    result.matrix[1] = u.x;
    result.matrix[5] = u.y;
    result.matrix[9] = u.z;
    
    result.matrix[2] = -f.x;
    result.matrix[6] = -f.y;
    result.matrix[10] = -f.z;
    
    result.matrix[12] = -Vector3::dot(s, eye);
    result.matrix[13] = -Vector3::dot(u, eye);
    result.matrix[14] = Vector3::dot(f, eye);
    
    result.matrix[3] = 0;
    result.matrix[7] = 0;
    result.matrix[11] = 0;
    result.matrix[15] = 1;
    
    return result;
}

Matrix4x4 Matrix4x4::createPerspective(const GLfloat near, const GLfloat far, const GLfloat fovY_degree, const GLfloat aspect)
{
    Matrix4x4 result;
    
    const GLfloat f = (GLfloat) (1.0f / (tan(Deg2Rad(fovY_degree))/2.0f));
    
    result.matrix[0] = f / aspect;
    result.matrix[5] = f;
    result.matrix[10] = (far + near) / (near - far);
    result.matrix[11] = -1;
    result.matrix[14] = (2.0f * far * near) / (near - far);
    result.matrix[15] = 0.0f;
    
    return result;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4 m)
{
    *this = multiply(*this, m);
    
    return *this;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 m)
{
    return multiply(*this, m);
}










