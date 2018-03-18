//
//  Camera.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/03/19.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera():
_cameraPos(Vector3(0.0f,0.0f,-5.0f)),
_lookAt(Vector3(0.0f,0.0f,0.0f)),
_cameraUp(Vector3(0.0f,1.0f,0.0f)),
_near(1.0f),
_far(100.0f),
_fovYDeg(45.0f)
{
    auto app = Application::getInstance();
    _aspect = (GLfloat)(app->getSurfaceWidth()) / (GLfloat)(app->getSurfaceHeight());
}

Camera::Camera(Vector3 pos,Vector3 lookAt,Vector3 cameraUp,GLfloat near,GLfloat far,GLfloat fovYDeg,GLfloat aspect):
_cameraPos(pos),
_lookAt(lookAt),
_cameraUp(cameraUp),
_near(near),
_far(far),
_fovYDeg(fovYDeg),
_aspect(aspect)
{
    
}

void Camera::SetCameraPos(Vector3 pos)
{
    _cameraPos = pos;
}

void Camera::SetLookAt(Vector3 pos, Vector3 lookAt,Vector3 cameraUp)
{
    _cameraPos = pos;
    _lookAt = lookAt;
    _cameraUp = cameraUp;
}

void Camera::SetProjection(GLfloat near, GLfloat far, GLfloat fovYDeg, GLfloat aspect)
{
    _near = near;
    _far = far;
    _fovYDeg = fovYDeg;
    _aspect = aspect;
}

void Camera::GetLookAtProjection(Matrix4x4 &lookAt, Matrix4x4& projection)
{
    lookAt = Matrix4x4::createLookAt(_cameraPos, _lookAt, _cameraUp);
    projection = Matrix4x4::createPerspective(_near, _far, _fovYDeg, _aspect);
}







