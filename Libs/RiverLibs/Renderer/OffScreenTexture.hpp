//
//  OffScreenTexture.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/08/01.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef OffScreenTexture_hpp
#define OffScreenTexture_hpp

#include "river.h"

class OffScreenTexture : public ObjectInterface
{
    GLuint _frameBuffer;
    GLuint _colorTexture;
    GLuint _depthBuffer;
    GLint _defFrameBuffer;
    
    int _width,_height;
public:
    OffScreenTexture(int width,int height);
    virtual ~OffScreenTexture(){}
    
    virtual bool init()override;
    
};

#endif /* OffScreenTexture_hpp */
