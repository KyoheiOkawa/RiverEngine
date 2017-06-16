//
//  Matrix4x4.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/16.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Matrix4x4_hpp
#define Matrix4x4_hpp

#include <stdio.h>

class Vector3;

class Matrix4x4
{
public:
    float matrix[16];
    
    Matrix4x4();
    
    void identity();
    
    void transpose();
    
    static Matrix4x4 createTranslate(const float x, const float y, const float z);
    
    static Matrix4x4 createScale(const float x,const float y, float z);
    
    static Matrix4x4 createRotate(const Vector3 axis, const float rotate);
    
    static Matrix4x4 multiply(const Matrix4x4 a,const Matrix4x4 b);
};
#endif /* Matrix4x4_hpp */
