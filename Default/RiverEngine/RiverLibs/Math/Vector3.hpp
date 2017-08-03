//
//  Vector3.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Vector3_hpp
#define Vector3_hpp

#include <stdio.h>
#include <math.h>

class Vector3
{
public:
    float x;
    float y;
    float z;
    
    Vector3();
    Vector3(float xi, float yi, float zi);
    
    static Vector3 ZERO();
    static Vector3 ONE();
    static Vector3 RIGHT();
    static Vector3 UP();
    static Vector3 FORWARD();
    
    static float dot(const Vector3& v1, const Vector3& v2);
    static float angle(Vector3& v1, Vector3& v2);
    
    float magnitude() const;
    void normalize();
    Vector3 getNormalized() const;
    void reverse();
    float dot(const Vector3 &v) const;
    Vector3 cross(const Vector3 &v) const;
    void set(float xi, float yi, float zi);
    
    Vector3& operator=(const Vector3& other);
    Vector3& operator+=(Vector3 u);
    Vector3& operator-=(Vector3 u);
    Vector3& operator*=(float s);
    Vector3& operator/=(float s);
    Vector3 operator-();
    Vector3 operator+(const Vector3& u);
    Vector3 operator-(const Vector3& u);
    Vector3 operator*(float f);
    Vector3 operator^(const Vector3& u);
    
};



#endif /* Vector3_hpp */
