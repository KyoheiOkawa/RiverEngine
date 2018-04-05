//
//  Vertex.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/08/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include "stdinc.h"

struct PositionTexture
{
    GLfloat position[3];
    GLfloat uv[2];
};

struct PositionColor
{
    GLfloat position[3];
    GLbyte color[3];
};

struct PositionColorTexture
{
    GLfloat position[3];
    GLbyte color[3];
    GLfloat uv[2];
};

struct PositionNormal
{
    GLfloat position[3];
    GLfloat normal[3];
};

#endif /* Vertex_hpp */
