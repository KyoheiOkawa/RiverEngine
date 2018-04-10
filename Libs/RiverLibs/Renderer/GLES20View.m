//
//  GLES20View.m
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#import "GLES20View.h"
#import <QuartzCore/QuartzCore.h>

@implementation GLES20View

@synthesize rendering_height;
@synthesize rendering_width;

+ (Class) layerClass{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if(self){
        CAEAGLLayer *pLayer = (CAEAGLLayer*)self.layer;
        pLayer.opaque = TRUE;
        pLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:FALSE],kEAGLDrawablePropertyRetainedBacking,
                                   kEAGLColorFormatRGBA8,kEAGLDrawablePropertyColorFormat, nil];
    }
    
    return self;
}

- (void)layoutSubviews{
    NSLog(@"layoutSubViews");
    [super layoutSubviews];
    
    @synchronized (self) {
        if(![self ready]){
            NSLog(@"Initialize OpenGL ES 2.0");
            [self initGLES20];
        }
        
        [self resizeRenderBuffer];
        [self unbindGL];
        
        initialized = YES;
    }
}

- (EAGLContext*) renderingContext{
    return renderingContext;
}

- (void) resizeRenderBuffer {
    {
        const BOOL curent = [EAGLContext setCurrentContext:renderingContext];
        assert(curent == TRUE);
    }
    
    const float scaleFactor = [self contentScaleFactor];
    const int rendering_buffer_width = (int)(self.bounds.size.width * scaleFactor);
    const int rendering_buffer_height = (int)(self.bounds.size.height * scaleFactor);
    NSLog(@"Rendering Request Size(%d x %d)",rendering_buffer_width,
           rendering_buffer_height);
    
    {
        glBindRenderbuffer(GL_RENDERBUFFER,buffer_color);
        const BOOL complete = [renderingContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer];
        assert(complete == TRUE);
        
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH,&rendering_width);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &rendering_height);
        
        NSLog(@"Rendering Buffer Size(%d x %d)",rendering_width,rendering_height);
        assert(rendering_width == rendering_buffer_width);
        assert(rendering_height == rendering_buffer_height);
    }
    
    {
        glBindRenderbuffer(GL_RENDERBUFFER, buffer_depth_stencil);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, rendering_width, rendering_height);
        
        GLint depth_stencil_width = 0;
        GLint depth_stencil_height = 0;
        
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &depth_stencil_width);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &depth_stencil_height);
        
        NSLog(@"Depth&Stencil Buffer Size(%d x %d)",
               depth_stencil_width,depth_stencil_height);
        assert(depth_stencil_width == rendering_buffer_width);
        assert(depth_stencil_height == rendering_buffer_height);
    }
    
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    assert(glGetError() == GL_NO_ERROR);
    
    glBindFramebuffer(GL_FRAMEBUFFER, buffer_frame);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, buffer_color);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer_depth_stencil);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer_depth_stencil);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    {
        const BOOL current = [EAGLContext setCurrentContext:nil];
        assert(current == TRUE);
    }
}

- (void)initGLES20{
    self.contentScaleFactor = [UIScreen mainScreen].scale;
    
    renderingContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    {
        BOOL current = [EAGLContext setCurrentContext:renderingContext];
        assert(current == TRUE);
    }
    
    glGenFramebuffers(1, &buffer_frame);
    assert(buffer_frame);
    
    glGenRenderbuffers(1, &buffer_color);
    assert(buffer_color);
    
    glGenRenderbuffers(1, &buffer_depth_stencil);
    assert(buffer_depth_stencil);
    
    {
        BOOL current = [EAGLContext setCurrentContext:nil];
        assert(current == TRUE);
    }
}

- (void)disposeGLES20{
    if(renderingContext == nil){
        NSLog(@"self disposed");
        return;
    }
    
    glGetError();
    BOOL current = [EAGLContext setCurrentContext:renderingContext];
    assert(current == TRUE);
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        assert(glGetError() == GL_NO_ERROR);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        assert(glGetError() == GL_NO_ERROR);
    }
    
    {
        glDeleteFramebuffers(1, &buffer_frame);
        buffer_frame = 0;
        assert(glGetError() == GL_NO_ERROR);
        
        glDeleteRenderbuffers(1, &buffer_color);
        buffer_color = 0;
        assert(glGetError() == GL_NO_ERROR);
        
        glDeleteRenderbuffers(1, &buffer_depth_stencil);
        buffer_depth_stencil = 0;
        assert(glGetError() == GL_NO_ERROR);
    }
    current = [EAGLContext setCurrentContext:nil];
    assert(current == TRUE);
    renderingContext = nil;
}

- (BOOL)ready{
    return initialized;
}

- (void)bindGL{
    BOOL current = [EAGLContext setCurrentContext:renderingContext];
    assert(current == TRUE);
    glBindFramebuffer(GL_FRAMEBUFFER, buffer_frame);
    glBindRenderbuffer(GL_RENDERBUFFER, buffer_color);
}

- (void)unbindGL{
    BOOL current = [EAGLContext setCurrentContext:nil];
    assert(current == TRUE);
}

- (void)postFrontBuffer{
    glBindRenderbuffer(GL_RENDERBUFFER, buffer_color);
    [renderingContext presentRenderbuffer:GL_RENDERBUFFER];
}

@end

