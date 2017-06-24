//
//  Texture2D.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/24.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp

#include <stdio.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include "Helper.hpp"
#include <memory>

/**
 * RGBA各8bit色
 *
 * 32bit / pixel
 */
#define TEXTURE_RAW_RGBA8         0

/**
 * RGB各8bit色
 *
 * 24bit / pixel
 */
#define TEXTURE_RAW_RGB8          1

/**
 * RGB各5bit
 * A 1bit
 *
 * 16bit / pixel
 */
#define TEXTURE_RAW_RGBA5551     2

/**
 * R 5bit
 * G 6bit
 * B 5bit
 *
 * 16bit/ pixel
 */
#define TEXTURE_RAW_RGB565       3

typedef struct Texture2D
{
    int width;
    
    int height;
    
    GLuint id;
} Texture2D;

/**
 * 引数sizeがpotならtrueを返す。
 */
extern bool Texture2D_checkPowerOfTwo(const int size);

/**
 * 引数width/height共にがpotならtrueを返す。
 */
extern bool Texture2D_checkPowerOfTwoWH(const int width, const int height);

///**
// * 画像をテクスチャとして読み込む。
// * 読み込んだ画像はes20_freeTexture()で解放する
// */
//extern Texture2D* Texture2D_load(const char* file_name, const int pixel_fotmat);

/**
 * テクスチャの縦横が2のn乗であればtrueを返す
 */
extern bool Texture2D_isPowerOfTwo(Texture2D *texture);

/**
 * テクスチャを解放する。
 */
extern void Texture2D_free(Texture2D *texture);

#endif /* Texture2D_hpp */
