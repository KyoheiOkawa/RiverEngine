//
//  Quaternion.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/04/02.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Quaternion.hpp"
#include "Vector3.hpp"
#include "Matrix4x4.hpp"
#include "MathMacro.h"

const Quaternion Quaternion::ZERO(0.0f,0.0f,0.0f,0.0f);

Quaternion::Quaternion()
{
    x = 0;
    y = 0;
    z = 0;
    w = 1;
}

Quaternion::Quaternion(float xx,float yy,float zz,float ww)
{
    set(xx,yy,zz,ww);
}

Quaternion::Quaternion(const Matrix4x4& m)
{
    set(m);
}

Quaternion::Quaternion(const Vector3& axis, float angleRad)
{
    set(axis,angleRad);
}

Quaternion::Quaternion(const Quaternion& copy)
{
    set(copy);
}

const Quaternion& Quaternion::identity()
{
    static Quaternion value(0.0f,0.0f,0.0f,1.0f);
    return value;
}

const Quaternion& Quaternion::zero()
{
    static Quaternion value(0.0f,0.0f,0.0f,0.0f);
    return value;
}

bool Quaternion::isIdentity() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
}

bool Quaternion::isZero() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

void Quaternion::createFromRotationMatrix(const Matrix4x4& m, Quaternion* dst)
{
    m.getRotation(dst);
}

void Quaternion::createFromAxisAngle(const Vector3 &axis, float angleRad, Quaternion *dst)
{
    float halfAngle = angleRad * 0.5f;
    float sinHalfAngle = sinf(halfAngle);
    
    Vector3 normal(axis);
    normal.normalize();
    dst->x = normal.x * sinHalfAngle;
    dst->y = normal.y * sinHalfAngle;
    dst->z = normal.z * sinHalfAngle;
    dst->w = cosf(halfAngle);
}

void Quaternion::conjugate()
{
    x = -x;
    y = -y;
    z = -z;
}

Quaternion Quaternion::getConjugated() const
{
    Quaternion q(*this);
    q.conjugate();
    return q;
}

bool Quaternion::inverse()
{
    float n = x * x + y * y + z * z + w * w;
    if (n == 1.0f)
    {
        x = -x;
        y = -y;
        z = -z;
        //w = w;
        
        return true;
    }
    
    // Too close to zero.
    if (n < 0.000001f)
        return false;
    
    n = 1.0f / n;
    x = -x * n;
    y = -y * n;
    z = -z * n;
    w = w * n;
    
    return true;
}

Quaternion Quaternion::getInversed() const
{
    Quaternion q(*this);
    q.inverse();
    return q;
}

void Quaternion::multiply(const Quaternion& q)
{
    multiply(*this, q, this);
}

void Quaternion::multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst)
{
    float x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    float y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    float z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    float w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    
    dst->x = x;
    dst->y = y;
    dst->z = z;
    dst->w = w;
}

void Quaternion::normalize()
{
    float n = x * x + y * y + z * z + w * w;
    
    // Already normalized.
    if (n == 1.0f)
        return;
    
    n = std::sqrt(n);
    // Too close to zero.
    if (n < 0.000001f)
        return;
    
    n = 1.0f / n;
    x *= n;
    y *= n;
    z *= n;
    w *= n;
}

Quaternion Quaternion::getNormalized() const
{
    Quaternion q(*this);
    q.normalize();
    return q;
}

void Quaternion::set(float xx, float yy, float zz, float ww)
{
    x = xx;
    y = yy;
    z = zz;
    w = ww;
}

void Quaternion::set(const Matrix4x4 &m)
{
    Quaternion::createFromRotationMatrix(m, this);
}

void Quaternion::set(const Vector3 &axis, float angleRad)
{
    Quaternion::createFromAxisAngle(axis, angleRad, this);
}

void Quaternion::set(const Quaternion &q)
{
    this->x = q.x;
    this->y = q.y;
    this->z = q.z;
    this->w = q.w;
}

void Quaternion::setIdentity()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

float Quaternion::toAxisAngle(Vector3* axis) const
{
    Quaternion q(x, y, z, w);
    q.normalize();
    axis->x = q.x;
    axis->y = q.y;
    axis->z = q.z;
    axis->normalize();
    
    return (2.0f * std::acos(q.w));
}

Vector3 Quaternion::toRotVec() const
{
    Quaternion temp = *this;
    temp.normalize();
    Matrix4x4 mt = Matrix4x4::createRotate(temp);
    Vector3 rot;
    if(mt.matrix[6] == 1.0f)
    {
        rot.x = PI / 2.0f;
        rot.y = 0.0f;
        rot.z = -atan2(mt.matrix[5], mt.matrix[0]);
    }
    else if(mt.matrix[6] == -1.0f)
    {
        rot.x = -PI / 2.0f;
        rot.y = 0.0f;
        rot.z = -atan2(mt.matrix[5], mt.matrix[0]);
    }
    else
    {
        rot.x = -asin(mt.matrix[6]);
        rot.y = -atan2(-mt.matrix[2], mt.matrix[10]);
        rot.z = atan2(mt.matrix[4], mt.matrix[0]);
    }
    return rot;
}

Quaternion& Quaternion::operator*=(const Quaternion &q)
{
    multiply(q);
    return *this;
}

inline Vector3 Quaternion::operator*(const Vector3& v) const
{
    Vector3 uv,uuv;
    Vector3 qvec(x,y,z);
    uv = Vector3::cross(qvec, v);
    uuv = Vector3::cross(qvec, uv);
    
    uv *= (2.0f * w);
    uuv *= 2.0f;
    
    return v + uv + uuv;
}

