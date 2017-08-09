//
//  Sprite.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <memory>

class Sprite : public GameObject
{
    Vector2 _spriteSize;
    
    GLProgram* _useProgram;
    
    GLint _attr_pos;
    GLint _unif_matrix;
    GLint _attr_uv;
    GLint _unif_texture;
    GLuint _texture_id;
    
public:
    Sprite();
    virtual ~Sprite();
    
    
    virtual void setUseProgram(GLProgram* program){
        _useProgram = program;
    }
    
    static std::shared_ptr<Sprite> create();
    
    static std::shared_ptr<Sprite> createWithTexture(std::string texKey);
    
    virtual bool init() override;
    
    virtual void update() override;
    
    virtual void draw() override;
    
    virtual void onScreenTouched(TouchInfo& touchInfo) override;
    
    void setTexture(std::string texKey);
    
    Vector2 getSpriteSize(){
        return _spriteSize;
    }
};

#endif /* Sprite_hpp */
