//
//  GLES20View.h
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>

@interface GLES20View : UIView
{
    EAGLContext *renderingContext;
    
    GLuint buffer_depth_stencil;
    
    GLuint buffer_color;
    
    GLuint buffer_frame;
    
    GLint rendering_width;
    
    GLint rendering_height;
    
    BOOL initialized;
}

@property (readonly) GLint rendering_width;
@property (readonly) GLint rendering_height;

- (EAGLContext*) renderingContext;

- (void) initGLES20;

- (void) disposeGLES20;

- (void) bindGL;

- (void) unbindGL;

- (void) postFrontBuffer;

- (BOOL) ready;

@end
