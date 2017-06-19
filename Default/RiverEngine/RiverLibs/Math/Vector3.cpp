//
//  Vector3.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "Vector3.hpp"

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float xi, float yi, float zi)
{
    x = xi;
    y = yi;
    z = zi;
}

float Vector3::magnitude()
{
    return sqrtf(x*x + y*y + z*z);
}

void Vector3::normalize()
{
    float m = sqrtf(x*x + y*y + z*z);
    if(m <= tol) m = 1;
    x /= m;
    y /= m;
    z /= m;
    
    if(fabs(x) < tol) x = 0.0f;
    if(fabs(y) < tol) y = 0.0f;
    if(fabs(z) < tol) z = 0.0f;
}

Vector3 Vector3::getNormalized()
{
    Vector3 tmp;
    
    float m = sqrtf(x*x + y*y + z*z);
    if(m <= tol) m = 1;
    tmp.x = x / m;
    tmp.y = y / m;
    tmp.z = z / m;
    
    if(fabs(tmp.x) < tol) tmp.x = 0.0f;
    if(fabs(tmp.y) < tol) tmp.y = 0.0f;
    if(fabs(tmp.z) < tol) tmp.z = 0.0f;
    
    return tmp;
}

void Vector3::reverse()
{
    x = -x;
    y = -y;
    z = -z;
}

float Vector3::dot(const Vector3 &v) const
{
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3 &v) const
{
    return Vector3(y * v.z - z * v.y,
                   z * v.x - x * v.z,
                   x * v.y - y * v.x);
}

Vector3& Vector3::operator+=(Vector3 u)
{
    x += u.x;
    y += u.y;
    z += u.z;
    
    return *this;
}

Vector3& Vector3::operator-=(Vector3 u)
{
    x -= u.x;
    y -= u.y;
    z -= u.z;
    
    return *this;
}

Vector3& Vector3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    
    return *this;
}

Vector3& Vector3::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
    
    return *this;
}

Vector3& Vector3::operator=(const Vector3& other){
    //自己代入の抑制
    if(this != &other){
        x = other.x;
        y = other.y;
        z = other.z;
    }
    
    return *this;
}

Vector3 Vector3::operator-()
{
    return Vector3(-x,-y,-z);
}

Vector3 Vector3::operator+(const Vector3& u)
{
    Vector3 tmp;
    tmp.x = x + u.x;
    tmp.y = y + u.y;
    tmp.z = z + u.z;
    
    return tmp;
}

Vector3 Vector3::operator-(const Vector3& u)
{
    Vector3 tmp;
    tmp.x = x - u.x;
    tmp.y = y - u.y;
    tmp.z = z - u.z;
    
    return tmp;
}

Vector3 Vector3::operator*(float f)
{
    Vector3 tmp;
    tmp.x = x*f;
    tmp.y = y*f;
    tmp.z = z*f;
    
    return tmp;
}

Vector3 Vector3::operator^(const Vector3& u)
{
    Vector3 tmp;
    tmp.x = y * u.z - z * u.y;
    tmp.y = -x * u.z + z * u.x;
    tmp.z = x * u.y - y * u.x;
    
    return tmp;
}

Vector3 Vector3::ZERO(){
    return Vector3(0,0,0);
}

Vector3 Vector3::ONE(){
    return Vector3(1,1,1);
}

Vector3 Vector3::RIGHT(){
    return Vector3(1,0,0);
}

Vector3 Vector3::UP(){
    return Vector3(0,1,0);
}

Vector3 Vector3::FORWARD(){
    return Vector3(0,0,1);
}
