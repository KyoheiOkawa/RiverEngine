//
//  support_gl.h
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef __support_gl_h__
#define __support_gl_h__

#include "Application.h"
#import "ViewController.h"
#import "GLES20View.h"

extern int ES20_bind(Application* app);

extern void ES20_unbind(Application* app);

extern void ES20_postFrontBuffer(Application* app);

#define ES20_NO_ERROR 0
#define ES20_ERROR    1

#endif
