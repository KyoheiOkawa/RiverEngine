//
//  ViewController.m
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#import "ViewController.h"
#include <thread>
#include <chrono>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    running = NO;
    deleted = NO;
    
    glesView = [[GLES20View alloc] initWithFrame:[[UIScreen mainScreen]bounds]];
    
    [self setView:glesView];
    [self performSelectorInBackground:@selector(es20appLoop:) withObject:self];
}

-(void) showAbortDialocOnMainThread:(id)message{
    [[[UIAlertView alloc] initWithTitle:@"処理を中断します"
                         message:message
                         delegate:self
                         cancelButtonTitle:nil
                         otherButtonTitles:@"OK", nil] show];
}

-(void) showAbortDialog:(NSString *)message{
    [self performSelectorOnMainThread:@selector(showAbortDialocOnMainThread:) withObject:message waitUntilDone:NO];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidDisappear:(BOOL)animated
{
    deleted = YES;
    
    while(running){
        [NSThread sleepForTimeInterval:0.01];
    }
    [glesView disposeGLES20];
    [super viewWillDisappear:animated];
}

- (void)viewWillLayoutSubviews{
    [super viewWillLayoutSubviews];
    
    NSLog(@"viewWillLayoutSubview size(%d x %d)",(int)(glesView.bounds.size.width),(int)(glesView.bounds.size.height));
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation{
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];
}

- (void)es20worker:(id)item{
    EAGLContext *renderingContext = [glesView renderingContext];
    
    EAGLContext *workerContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 sharegroup:renderingContext.sharegroup];
    
    {
        BOOL complete = [EAGLContext setCurrentContext:workerContext];
        assert(complete);
    }
    
    //アプリケーションの非同期処理をここに記述する
    Application::getInstance()->async();
    
    {
        BOOL complete = [EAGLContext setCurrentContext:nil];
        assert(complete);
    }
    
    workerContext = nil;
}

- (void)es20appLoop:(id)item{
    while(!deleted && ![glesView ready]){
        [NSThread sleepForTimeInterval:0.01];
    }
    if(deleted){
        return;
    }
    
    running = YES;
    
    Application* app = Application::getInstance();
    app->setGLESView((__bridge void*)glesView);
    app->setViewController((__bridge void*)self);
    app->setSurfaceWidth(glesView.rendering_width);
    app->setSurfaceHeight(glesView.rendering_height);
    
    ES20_bind(app);
    
    app->initialize();
    glViewport(0, 0, app->getSurfaceWidth(), app->getSurfaceHeight());
    
    [self performSelectorInBackground:@selector(es20worker:) withObject:self];
    
    std::chrono::steady_clock::time_point start,end;
    while(!deleted)
    {
        @synchronized (glesView)
        {
            start = std::chrono::steady_clock::now();
            
            if(app->getSurfaceWidth() != glesView.rendering_width ||
               app->getSurfaceHeight() != glesView.rendering_height)
            {
                app->setSurfaceWidth(glesView.rendering_width);
                app->setSurfaceHeight(glesView.rendering_height);
                
                app->resized();
            }
            
            app->update();
            app->rendering();
            
            end = std::chrono::steady_clock::now();
            
            auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            app->setDeltaTIme(delta / 1000.0f);
        }
    }
    
    app->destroy();
    ES20_unbind(app);
}

///ステータスバーを非表示にする
- (BOOL) prefersStatusBarHidden{
    return YES;
}

@end
