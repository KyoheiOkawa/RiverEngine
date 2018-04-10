//
//  Camera.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/03/19.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "stdinc.h"
#include "river.h"

class Camera
{
    Vector3 _cameraPos;
    Vector3 _lookAt;
    Vector3 _cameraUp;
    GLfloat _near;
    GLfloat _far;
    GLfloat _fovYDeg;
    GLfloat _aspect;
    
public:
    Camera();
    Camera(Vector3 pos,Vector3 lookAt,Vector3 cameraUp,GLfloat near,GLfloat far,GLfloat fovYDeg,GLfloat aspect);
    virtual ~Camera(){}
    
    void SetCameraPos(Vector3 pos);
    void SetLookAt(Vector3 pos,Vector3 lookAt,Vector3 cameraUp);
    void SetProjection(GLfloat near,GLfloat far,GLfloat fovYDeg,GLfloat aspect);
    
    Vector3 GetCameraPos(){return _cameraPos;}
    Vector3 GetLookAt(){return _lookAt;}
    GLfloat GetNear(){return _near;}
    GLfloat GetFar(){return _far;}
    GLfloat GetFovYDegree(){return _fovYDeg;}
    GLfloat GetAspect(){return _aspect;}
    
    void GetLookAtProjection(Matrix4x4& lookAt,Matrix4x4& projection);
};

#endif /* Camera_hpp */
