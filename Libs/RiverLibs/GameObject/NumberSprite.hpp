//
//  NumberSprite.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/10.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef NumberSprite_hpp
#define NumberSprite_hpp

#include "river.h"

class NumberSprite : public GameObject
{
    Vector2 _spriteSize;
    
    GLProgram* _useProgram;
    
    GLint _attr_pos;
    GLint _unif_matrix;
    GLint _attr_uv;
    GLint _unif_texture;
    GLuint _texture_id;
    
    string _texKey;
    unsigned int _number;
    
    ///数字と数字の間の距離
    float _numDistance = 0.6f;
    
    std::shared_ptr<MeshResource<PositionTexture>> _meshResource;
    
    unsigned int calcOddCenterIndex(unsigned int digit){return ((digit-1)/2);}
public:
    NumberSprite();
    virtual ~NumberSprite();
    
    
    virtual void setUseProgram(GLProgram* program){
        _useProgram = program;
    }
    
    static std::shared_ptr<NumberSprite> create(string texKey,unsigned int number);
    
    virtual bool init() override;
    
    virtual void update() override;
    
    virtual void draw() override;
};

#endif /* NumberSprite_hpp */
