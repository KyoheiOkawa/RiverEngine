//
//  OffScreenTexture.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/08/01.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "OffScreenTexture.hpp"

OffScreenTexture::OffScreenTexture(int width,int height):
_width(width),
_height(height)
{
    
}

OffScreenTexture::~OffScreenTexture()
{
    glDeleteTextures(1, &_colorTexture);
    glDeleteRenderbuffers(1, &_depthBuffer);
    glDeleteFramebuffers(1, &_frameBuffer);
}

bool OffScreenTexture::init()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defFrameBuffer);
    assert(_defFrameBuffer != 0);
    
    glGenTextures(1, &_colorTexture);
    assert(glGetError() == GL_NO_ERROR);
    assert(_colorTexture != 0);
    
    glBindTexture(GL_TEXTURE_2D, _colorTexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    assert(glGetError() == GL_NO_ERROR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenRenderbuffers(1, &_depthBuffer);
    assert(glGetError()==GL_NO_ERROR);
    assert(_depthBuffer != 0);
    
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, _width, _height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    glGenFramebuffers(1, &_frameBuffer);
    assert(glGetError()==GL_NO_ERROR);
    assert(_frameBuffer != 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTexture, 0);
    assert(glGetError()==GL_NO_ERROR);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    assert(glGetError()==GL_NO_ERROR);
    
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE);
    
    glBindFramebuffer(GL_FRAMEBUFFER, _defFrameBuffer);
    
    return true;
}

void OffScreenTexture::begin()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    assert(glGetError()==GL_NO_ERROR);
    
    glViewport(0, 0, _width, _height);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OffScreenTexture::end()
{
    auto app = Application::getInstance();
    glBindFramebuffer(GL_FRAMEBUFFER, _defFrameBuffer);
    glViewport(0, 0, app->getSurfaceWidth(), app->getSurfaceHeight());
}
