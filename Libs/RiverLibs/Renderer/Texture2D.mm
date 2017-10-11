//
//  Texture2D.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/24.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "Texture2D.h"

/**
 * サイズがpotならTEXTURE_POTを返す。npotなら、TEXTURE_NPOTを返す。
 */
bool Texture2D_checkPowerOfTwo(const int size) {
    int bit = 1;
    int i = 0;
    const int BIT_SIZE = sizeof(int) * 8;
    
    if (!size) {
        return false;
    }
    
    for (i = 0; i < BIT_SIZE; ++i) {
        if (size == bit) {
            return true;
        }
        bit <<= 1;
    }
    
    return false;
}

/**
 * 引数sizeがpotならTEXTURE_POTを返す。npotなら、TEXTURE_NPOTを返す。
 */
bool Texture2D_checkPowerOfTwoWH(const int width, const int height) {
    return Texture2D_checkPowerOfTwo(width) && Texture2D_checkPowerOfTwo(height);
}


/**
 * テクスチャの縦横が2のn乗であればtrueを返す
 */
bool Texture2D_isPowerOfTwo(Texture2D *texture) {
    return Texture2D_checkPowerOfTwo(texture->width) && Texture2D_checkPowerOfTwo(texture->height);
}

/**
 * テクスチャを解放する。
 */
void Texture2D_free(Texture2D *texture) {
    glDeleteTextures(1, &texture->id);
    free((void*) texture);
}
