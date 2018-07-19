//
//  Matrix4x4.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/16.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Quaternion.hpp"
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

bool Matrix4x4::decompose(Vector3* scale, Quaternion* rotation, Vector3* translation) const
{
    if(translation)
    {
        translation->x = matrix[12];
        translation->y = matrix[13];
        translation->z = matrix[14];
    }
    
    if(scale == nullptr && rotation == nullptr)
        return true;
    
    Vector3 xaxis(matrix[0],matrix[1],matrix[2]);
    float scaleX = xaxis.magnitude();
    
    Vector3 yaxis(matrix[4],matrix[5],matrix[6]);
    float scaleY = yaxis.magnitude();
    
    Vector3 zaxis(matrix[8],matrix[9],matrix[10]);
    float scaleZ = zaxis.magnitude();
    
    float det = determinant();
    if(det < 0)
        scaleZ = -scaleZ;
    
    if(scale)
    {
        scale->x = scaleX;
        scale->y = scaleY;
        scale->z = scaleZ;
    }
    
    if(rotation == nullptr)
        return true;
    
    if(scaleX < MATH_TOLERANCE || scaleY < MATH_TOLERANCE || std::abs(scaleZ) < MATH_TOLERANCE)
        return false;
    
    float rn;
    
    rn = 1.0f / scaleX;
    xaxis.x *= rn;
    xaxis.y *= rn;
    xaxis.z *= rn;
    
    rn = 1.0f / scaleY;
    yaxis.x *= rn;
    yaxis.y *= rn;
    yaxis.z *= rn;
    
    rn = 1.0f / scaleZ;
    zaxis.x *= rn;
    zaxis.y *= rn;
    zaxis.z *= rn;
    
    float trace = xaxis.x * yaxis.y * zaxis.z + 1.0f;
    
    if(trace > MATH_EPSILON)
    {
        float s = 0.5f / std::sqrt(trace);
        rotation->w = (yaxis.z - zaxis.y) * s;
        rotation->x = 0.25f / s;
        rotation->y = (yaxis.x + xaxis.y) * s;
        rotation->z = (zaxis.x + xaxis.z) * s;
    }
    else if(yaxis.y > zaxis.z)
    {
        float s = 0.5f / std::sqrt(1.0f + yaxis.y - xaxis.x - zaxis.z);
        rotation->w = (zaxis.x - xaxis.z) * s;
        rotation->x = (yaxis.x + xaxis.y) * s;
        rotation->y = 0.25f / s;
        rotation->z = (zaxis.y + yaxis.z) * s;
    }
    else
    {
        float s = 0.5f / std::sqrt(1.0f + zaxis.z - xaxis.x - yaxis.y);
        rotation->w = (xaxis.y - yaxis.x ) * s;
        rotation->x = (zaxis.x + xaxis.z ) * s;
        rotation->y = (zaxis.y + yaxis.z ) * s;
        rotation->z = 0.25f / s;
    }
    
    return true;
}

void Matrix4x4::getScale(Vector3 *scale) const
{
    decompose(scale, nullptr, nullptr);
}

bool Matrix4x4::getRotation(Quaternion *rotation) const
{
    return decompose(nullptr, rotation, nullptr);
}

void Matrix4x4::getTranslation(Vector3 *translation) const
{
    decompose(nullptr, nullptr, translation);
}

float Matrix4x4::determinant()const
{
    float a0 = matrix[0] * matrix[5] - matrix[1] * matrix[4];
    float a1 = matrix[0] * matrix[6] - matrix[2] * matrix[4];
    float a2 = matrix[0] * matrix[7] - matrix[3] * matrix[4];
    float a3 = matrix[1] * matrix[6] - matrix[2] * matrix[5];
    float a4 = matrix[1] * matrix[7] - matrix[3] * matrix[5];
    float a5 = matrix[2] * matrix[7] - matrix[3] * matrix[6];
    float b0 = matrix[8] * matrix[13] - matrix[9] * matrix[12];
    float b1 = matrix[8] * matrix[14] - matrix[10] * matrix[12];
    float b2 = matrix[8] * matrix[15] - matrix[11] * matrix[12];
    float b3 = matrix[9] * matrix[14] - matrix[10] * matrix[13];
    float b4 = matrix[9] * matrix[15] - matrix[11] * matrix[13];
    float b5 = matrix[10] * matrix[15] - matrix[11] * matrix[14];
    
    // Calculate the determinant.
    return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
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

Matrix4x4 Matrix4x4::createRotate(const Quaternion &q)
{
    Matrix4x4 dst;
    
    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;
    
    float xx2 = q.x * x2;
    float yy2 = q.y * y2;
    float zz2 = q.z * z2;
    float xy2 = q.x * y2;
    float xz2 = q.x * z2;
    float yz2 = q.y * z2;
    float wx2 = q.w * x2;
    float wy2 = q.w * y2;
    float wz2 = q.w * z2;
    
    dst.matrix[0] = 1.0f - yy2 - zz2;
    dst.matrix[1] = xy2 + wz2;
    dst.matrix[2] = xz2 - wy2;
    dst.matrix[3] = 0.0f;
    
    dst.matrix[4] = xy2 - wz2;
    dst.matrix[5] = 1.0f - xx2 - zz2;
    dst.matrix[6] = yz2 + wx2;
    dst.matrix[7] = 0.0f;
    
    dst.matrix[8] = xz2 + wy2;
    dst.matrix[9] = yz2 - wx2;
    dst.matrix[10] = 1.0f - xx2 - yy2;
    dst.matrix[11] = 0.0f;
    
    dst.matrix[12] = 0.0f;
    dst.matrix[13] = 0.0f;
    dst.matrix[14] = 0.0f;
    dst.matrix[15] = 1.0f;
    
    return dst;
}

Matrix4x4 Matrix4x4::createRotate(const Vector3 axis, const float angleDeg)
{
    Matrix4x4 ret;
    
    const float x = axis.x;
    const float y = axis.y;
    const float z = axis.z;
    
    const float c = cosf(Deg2Rad(angleDeg));
    const float s = sinf(Deg2Rad(angleDeg));
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
    
    const GLfloat xScale = ((GLfloat)spriteSize.x / (GLfloat) screenSize.x * 2.0f)*scale.x;
    const GLfloat yScale = ((GLfloat)spriteSize.y / (GLfloat) screenSize.x * 2.0f)*scale.y;
    
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

void Matrix4x4::rotate(const Quaternion &q)
{
    rotate(q, this);
}

void Matrix4x4::rotate(const Quaternion &q, Matrix4x4 *dst) const
{
    Matrix4x4 r;
    r = createRotate(q);
    *dst = multiply(*this, r);
}

void Matrix4x4::rotate(const Vector3 &axis, float angleRad)
{
    rotate(axis,angleRad,this);
}

void Matrix4x4::rotate(const Vector3 &axis, float angleRad, Matrix4x4 *dst) const
{
    Matrix4x4 r;
    r = createRotate(axis, Rad2Deg(angleRad));
    *dst = multiply(*this, r);
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










