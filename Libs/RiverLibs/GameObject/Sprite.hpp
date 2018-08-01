//
//  Sprite.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/09.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include "stdinc.h"

class Sprite : public GameObject
{
    Vector2 _spriteSize;
    
    GLProgram* _useProgram;
    
    GLint _attr_pos;
    GLint _unif_matrix;
    GLint _attr_uv;
    GLint _unif_texture;
    GLuint _texture_id;
    
    bool _is3DWorld;
    
    std::shared_ptr<MeshResource<PositionTexture>> _meshResource;
public:
    Sprite();
    virtual ~Sprite();
    
    
    virtual void setUseProgram(GLProgram* program){
        _useProgram = program;
    }
    
    static std::shared_ptr<Sprite> create();
    
    static std::shared_ptr<Sprite> createWithTexture(std::string texKey);
    static std::shared_ptr<Sprite> createWithTextureID(int width, int height,GLuint texID);
    
    virtual bool init() override;
    
    virtual void update() override;
    
    virtual void draw() override;
    
    void setTexture(std::string texKey);
    void setTexture(int width,int height, GLuint texID);
    
    void setIs3DWorld(bool b){_is3DWorld = b;}
    
    bool getIs3DWorld(){return _is3DWorld;}
    
    Vector2 getSpriteSize(){
        return _spriteSize;
    }
};

#endif /* Sprite_hpp */
