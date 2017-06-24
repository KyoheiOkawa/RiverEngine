//
//  RawPixelImage.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/24.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#include "RawPixelImage.h"
#include "Texture2D.h"
#import <Foundation/Foundation.h>
#import "ViewController.h"
#import "GLES20View.h"
#include "Helper.hpp"
#include "FileUtils.hpp"

RawPixelImage* RawPixelImage_load(const char* file_name, const int pixel_format)
{
    int pixelsize = 0;
    
    switch(pixel_format){
        case TEXTURE_RAW_RGBA8:
            pixelsize = 4;
            break;
        case TEXTURE_RAW_RGB8:
            pixelsize = 3;
            break;
        case TEXTURE_RAW_RGB565:
        case TEXTURE_RAW_RGBA5551:
            pixelsize = 2;
            break;
    }
    
    assert(pixelsize > 0);
    
    NSString *fileName = [[NSString alloc] initWithFormat:@"Assets/%@",CSTR2NSSTRING(file_name)];
    UIImage *image = [UIImage imageNamed:fileName];
    if(!image){
        NSLog(@"image(%@) is nil...",fileName);
        return NULL;
    }
    
    CGImageRef raw_image = image.CGImage;
    
    RawPixelImage *result = (RawPixelImage*)malloc(sizeof(RawPixelImage));
    const int image_width = (int)CGImageGetWidth(raw_image);
    const int image_height = (int)CGImageGetHeight(raw_image);
    const int pixel_bytes = (int)CGImageGetBitsPerPixel(raw_image) / 8;
    
    UInt8 *rgba = (unsigned char*)malloc(image_width * image_height * 4);
    
    {
        result->foramt = pixel_format;
        result->pixel_data = (void*)rgba;
        result->width = image_width;
        result->height = image_height;
    }
    
    NSLog(@"image(%d bit) size(%d x %d) = %s",pixel_bytes * 8, image_width,image_height,Texture2D_checkPowerOfTwoWH(image_width, image_height) ?"power of two" : "non power of two");
    
    assert(pixel_bytes == 3 || pixel_bytes == 4);
    
    CGDataProviderRef provider = CGImageGetDataProvider(raw_image);
    CFDataRef data = CGDataProviderCopyData(provider);
    
    UInt8 *raw_pixels = (UInt8*)CFDataGetBytePtr(data);
    
    switch(pixel_bytes){
        case 3:
            RawPixelImage_convertColorRGB(raw_pixels, pixel_format, result->pixel_data, result->width * result->height);
            break;
        case 4:
            RawPixelImage_convertColorRGBA(raw_pixels, pixel_format, result->pixel_data, result->width * result->height);
            break;
    }
    
    CFRelease(data);
    image = nil;
    return result;
}

/**
 * RGB888のポインタをdst_pixelsへピクセル情報をコピーする。
 */
void RawPixelImage_convertColorRGB(const void *rgb888_pixels, const int pixel_format, void *dst_pixels, const int pixel_num) {
    // 残ピクセル数
    int pixels = pixel_num;
    unsigned char *src_rgb888 = (unsigned char *) rgb888_pixels;
    
    switch (pixel_format) {
        case TEXTURE_RAW_RGB565: {
            unsigned short *p = (unsigned short*) dst_pixels;
            while (pixels) {
                
                const int r = src_rgb888[0] & 0xff;
                const int g = src_rgb888[1] & 0xff;
                const int b = src_rgb888[2] & 0xff;
                
                (*p) = ((r >> 3) << 11) | ((g >> 2) << 5) | ((b >> 3));
                src_rgb888 += 3;
                ++p;
                --pixels;
            }
        }
            break;
        case TEXTURE_RAW_RGBA5551: {
            unsigned short *p = (unsigned short*) dst_pixels;
            while (pixels) {
                
                const int r = src_rgb888[0] & 0xff;
                const int g = src_rgb888[1] & 0xff;
                const int b = src_rgb888[2] & 0xff;
                const int a = 1;
                (*p) = ((r >> 3) << 11) | ((g >> 3) << 6) | ((b >> 3) << 1) | a;
                src_rgb888 += 3;
                ++p;
                --pixels;
            }
        }
            break;
        case TEXTURE_RAW_RGB8: {
            memcpy(dst_pixels, src_rgb888, pixels * 3);
        }
            break;
        case TEXTURE_RAW_RGBA8: {
            unsigned char *dst = (unsigned char*) dst_pixels;
            while (pixels) {
                
                dst[0] = src_rgb888[0];
                dst[1] = src_rgb888[1];
                dst[2] = src_rgb888[2];
                dst[3] = 0xFF;
                
                src_rgb888 += 3;
                dst += 4;
                --pixels;
            }
        }
            break;
    }
}
/**
 * RGBA8888のポインタをdst_pixelsへピクセル情報をコピーする。
 */
void RawPixelImage_convertColorRGBA(const void *rgba8888_pixels, const int pixel_format, void *dst_pixels, const int pixel_num) {
    // 残ピクセル数
    int pixels = pixel_num;
    unsigned char *src_rgba8888 = (unsigned char *) rgba8888_pixels;
    
    switch (pixel_format) {
        case TEXTURE_RAW_RGB565: {
            unsigned short *p = (unsigned short*) dst_pixels;
            while (pixels) {
                
                const int r = src_rgba8888[0] & 0xff;
                const int g = src_rgba8888[1] & 0xff;
                const int b = src_rgba8888[2] & 0xff;
                
                (*p) = ((r >> 3) << 11) | ((g >> 2) << 5) | ((b >> 3));
                src_rgba8888 += 4;
                ++p;
                --pixels;
            }
        }
            break;
        case TEXTURE_RAW_RGBA5551: {
            unsigned short *p = (unsigned short*) dst_pixels;
            while (pixels) {
                
                const int r = src_rgba8888[0] & 0xff;
                const int g = src_rgba8888[1] & 0xff;
                const int b = src_rgba8888[2] & 0xff;
                const int a = (src_rgba8888[3] & 0xff) > 0 ? 1 : 0;
                (*p) = ((r >> 3) << 11) | ((g >> 3) << 6) | ((b >> 3) << 1) | a;
                src_rgba8888 += 4;
                ++p;
                --pixels;
            }
        }
            break;
        case TEXTURE_RAW_RGB8: {
            unsigned char *dst = (unsigned char*) dst_pixels;
            while (pixels) {
                
                dst[0] = src_rgba8888[0];
                dst[1] = src_rgba8888[1];
                dst[2] = src_rgba8888[2];
                
                src_rgba8888 += 4;
                dst += 3;
                --pixels;
            }
        }
            break;
        case TEXTURE_RAW_RGBA8: {
            memcpy(dst_pixels, src_rgba8888, pixels * 4);
        }
            break;
    }
}

/**
 * 画像用に確保したメモリを解放する
 */
void RawPixelImage_free(RawPixelImage *image) {
    if (image) {
        if (image->pixel_data) {
            free(image->pixel_data);
            image->pixel_data = NULL;
        }
        free(image);
    }
}
