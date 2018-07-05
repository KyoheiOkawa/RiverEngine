//
//  Quaternion.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/04/02.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include "stdinc.h"

class Matrix4x4;
class Vector3;

class Quaternion
{
public:
    float x;
    float y;
    float z;
    float w;
    
    Quaternion();
    Quaternion(float xx,float yy,float zz,float ww);
    Quaternion(const Matrix4x4& m);
    Quaternion(const Vector3& axis,float angleRad);
    Quaternion(const Quaternion& copy);
    
    ~Quaternion(){}
    
    static const Quaternion& identity();
    static const Quaternion& zero();
    
    bool isIdentity() const;
    bool isZero() const;
    
    static void createFromRotationMatrix(const Matrix4x4& m, Quaternion* dst);
    static void createFromAxisAngle(const Vector3& axis,float angleRad,Quaternion* dst);
    
    void conjugate();
    Quaternion getConjugated() const;
    
    bool inverse();
    Quaternion getInversed() const;
    
    void multiply(const Quaternion& q);
    static void multiply(const Quaternion& q1, const Quaternion& q2,Quaternion* dst);
    
    void normalize();
    Quaternion getNormalized() const;
    
    void set(float xx,float yy, float zz, float ww);
    void set(const Matrix4x4& m);
    void set(const Vector3& axis, float angleRad);
    void set(const Quaternion& q);
    
    void setIdentity();
    
    float toAxisAngle(Vector3* e) const;
    
    inline Quaternion operator*(const Quaternion& q) const
    {
        Quaternion result(*this);
        result.multiply(q);
        return result;
    }
    inline Vector3 operator*(const Vector3& v) const;
    Quaternion& operator*=(const Quaternion& q);
    
    static const Quaternion ZERO;
};

#endif /* Quaternion_hpp */
