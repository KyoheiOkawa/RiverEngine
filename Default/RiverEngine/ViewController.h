//
//  ViewController.h
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/13.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RiverLibs/Renderer/GLES20View.h"
#import "RiverLibs/Base/Application.h"
#import "RiverLibs/Renderer/support_gl.h"

@interface ViewController : UIViewController
{
    GLES20View *glesView;
    
    BOOL running;
    
    BOOL deleted;
}

-(void) es20appLoop:(id)item;

-(void) es20worker:(id)item;

-(void) showAbortDialog:(NSString*) message;


@end

