//
//  Matrix4x4.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/16.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Matrix4x4_hpp
#define Matrix4x4_hpp

#include "stdinc.h"

class Vector3;
class Vector2;
class Quaternion;

class Matrix4x4
{
public:
    float matrix[16];
    
    Matrix4x4();
    
    void identity();
    
    void transpose();
    
    bool decompose(Vector3* scale, Quaternion* rotation, Vector3* translation) const;
    void getScale(Vector3* scale)const;
    bool getRotation(Quaternion* rotation)const;
    void getTranslation(Vector3* translation)const;
    
    float determinant() const;
    
    static Matrix4x4 createTranslate(const float x, const float y, const float z);
    
    static Matrix4x4 createScale(const float x,const float y, float z);
    
    static Matrix4x4 createRotate(const Quaternion& q);
    static Matrix4x4 createRotate(const Vector3 axis, const float angleDeg);
    
    static Matrix4x4 multiply(const Matrix4x4 a,const Matrix4x4 b);
    
    static Matrix4x4 create2DAffine(const Vector3 pos,const Vector2 spriteSize,const Vector3 scale,const float rot,const Vector2 screenSize, const Vector3 pivot);
    
    static Matrix4x4 createLookAt(const Vector3 eye,const Vector3 look,const Vector3 up);
    
    static Matrix4x4 createPerspective(const GLfloat near, const GLfloat far, const GLfloat fovY_degree,const GLfloat aspect);
    
    void rotate(const Quaternion& q);
    void rotate(const Quaternion& q, Matrix4x4* dst) const;
    void rotate(const Vector3& axis,float angleRad);
    void rotate(const Vector3& axis, float angleRad,Matrix4x4* dst) const;
    
    Matrix4x4& operator*=(const Matrix4x4 m);
    Matrix4x4 operator*(const Matrix4x4 m);
};
#endif /* Matrix4x4_hpp */
