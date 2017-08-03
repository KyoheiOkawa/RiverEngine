//
//  Vector2.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/08/03.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "Vector2.hpp"
#include "MathMacro.h"

Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2::Vector2(float xi, float yi)
{
    x = xi;
    y = yi;
}

float Vector2::magnitude() const
{
    return sqrtf(x*x + y*y);
}

void Vector2::normalize()
{
    float m = magnitude();
    if(m <= MATH_TOLERANCE) m = 1;
    x /= m;
    y /= m;
    
    if(fabs(x) < MATH_TOLERANCE) x = 0.0f;
    if(fabs(y) < MATH_TOLERANCE) y = 0.0f;
}

Vector2 Vector2::getNormalized() const
{
    Vector2 tmp;
    
    float m = magnitude();
    if(m <= MATH_TOLERANCE) m = 1;
    tmp.x = x / m;
    tmp.y = y / m;
    
    if(fabs(tmp.x) < MATH_TOLERANCE) tmp.x = 0.0f;
    if(fabs(tmp.y) < MATH_TOLERANCE) tmp.y = 0.0f;
    
    return tmp;
}

void Vector2::reverse()
{
    x = -x;
    y = -y;
}

float Vector2::dot(const Vector2& v) const
{
    return x * v.x + y * v.y;
}

void Vector2::set(float xi, float yi)
{
    x = xi;
    y = yi;
}

Vector2& Vector2::operator+=(Vector2 u)
{
    x += u.x;
    y += u.y;
    
    return *this;
}

Vector2& Vector2::operator-=(Vector2 u)
{
    x -= u.x;
    y -= u.y;
    
    return *this;
}

Vector2& Vector2::operator*=(float s)
{
    x *= s;
    y *= s;
    
    return  *this;
}

Vector2& Vector2::operator/=(float s)
{
    x /= s;
    y /= s;
    
    return *this;
}

Vector2& Vector2::operator=(const Vector2& other)
{
    if(this != &other)
    {
        x = other.x;
        y = other.y;
    }
    
    return *this;
}

Vector2 Vector2::operator-()
{
    return Vector2(-x,-y);
}

Vector2 Vector2::operator+(const Vector2& u)
{
    Vector2 tmp;
    tmp.x = x + u.x;
    tmp.y = y + u.y;
    
    return tmp;
}

Vector2 Vector2::operator-(const Vector2& u)
{
    Vector2 tmp;
    tmp.x = x - u.x;
    tmp.y = y - u.y;
    
    return tmp;
}

Vector2 Vector2::operator*(float f)
{
    Vector2 tmp;
    tmp.x = x*f;
    tmp.y = y*f;
    
    return tmp;
}

Vector2 Vector2::ZERO()
{
    return Vector2(0,0);
}

Vector2 Vector2::ONE()
{
    return Vector2(1,1);
}

Vector2 Vector2::RIGHT()
{
    return Vector2(1,0);
}

Vector2 Vector2::UP()
{
    return Vector2(0,1);
}

float Vector2::dot(const Vector2& v1, const Vector2& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

float Vector2::angle(Vector2& v1, Vector2& v2)
{
    float dz = v1.x * v2.y - v1.y * v2.x;
    return atan2f(fabsf(dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}





















