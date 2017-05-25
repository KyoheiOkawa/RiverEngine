//
//  suppoert_gl.m
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#import "support_gl.h"

int ES20_bind(Application *app){
    GLES20View *view = (__bridge GLES20View*)app->getGLESView();
    [view bindGL];
    return ES20_NO_ERROR;
}

void ES20_unbind(Application *app){
    GLES20View *view = (__bridge GLES20View*)app->getGLESView();
    [view unbindGL];
}

void ES20_postFrontBuffer(Application *app){
    GLES20View *view = (__bridge GLES20View*)app->getGLESView();
    [view postFrontBuffer];
}
