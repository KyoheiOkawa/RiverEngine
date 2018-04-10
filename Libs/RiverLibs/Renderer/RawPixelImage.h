//
//  RawPixelImage.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/24.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef RawPixelImage_hpp
#define RawPixelImage_hpp

#define TEXTURE_RAW_RGBA8 0

#define TEXTURE_RAW_RGB8 1

#define TEXTURE_RAW_RGBA5551 2

#define TEXTURE_RAW_RGB565 3

typedef struct RawPixelImage
{
    void* pixel_data;
    
    int width;
    
    int height;
    
    int foramt;
    
} RawPixelImage;

extern RawPixelImage* RawPixelImage_load(const char* file_name,const int pixel_foramat);

extern void RawPixelImage_free(RawPixelImage *image);

extern void RawPixelImage_convertColorRGB(const void *rgb888_pixels, const int pixel_format, void *dst_pixels, const int pixel_num);

extern void RawPixelImage_convertColorRGBA(const void *rgba8888_pizels,const int pixel_format, void *dst_pixels, const int pixel_num);

#endif /* RawPixelImage_hpp */
