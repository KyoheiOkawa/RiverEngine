//
//  Vector2.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/08/03.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Vector2_hpp
#define Vector2_hpp

#include <stdio.h>
#include <math.h>

class Vector3;

class Vector2
{
public:
    float x;
    float y;
    
    Vector2();
    Vector2(float xi, float yi);
    
    static Vector2 ZERO();
    static Vector2 ONE();
    static Vector2 RIGHT();
    static Vector2 UP();
    
    static float dot(const Vector2& v1, const Vector2& v2);
    static float angle(Vector2& v1, Vector2& v2);
    
    float magnitude() const;
    void normalize();
    Vector2 getNormalized() const;
    void reverse();
    float dot(const Vector2 &v) const;
    void set(float xi, float yi);
    
    Vector2& operator=(const Vector2& other);
    Vector2& operator=(const Vector3& other);
    Vector2& operator+=(Vector2 u);
    Vector2& operator-=(Vector2 u);
    Vector2& operator*=(float s);
    Vector2& operator/=(float s);
    Vector2 operator-();
    Vector2 operator+(const Vector2& u);
    Vector2 operator-(const Vector2& u);
    Vector2 operator*(float f);
};

#endif /* Vector2_hpp */
