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
    virtual ~OffScreenTexture();
    
    virtual bool init()override;
    
    ///このテクスチャに対しての描画開始処理
    void begin();
    ///このテクスチャに対しての描画終了処理
    void end();
    
    GLuint getTextureID(){return _colorTexture;}
};

#endif /* OffScreenTexture_hpp */
