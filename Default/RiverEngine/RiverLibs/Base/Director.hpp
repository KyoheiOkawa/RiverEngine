//
//  Director.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/05/14.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Director_hpp
#define Director_hpp

#include <stdio.h>
#include <memory.h>
#include <map>
#include <string>

class Scene;

struct TextureInfo
{
    GLuint id;
    float width;
    float height;
    bool isPod;
};

class Director{
private:
    Director(){}
    static Director* _director;
    std::shared_ptr<Scene> _scene;
    std::map<std::string,GLProgram*> _programMap;
    std::map<std::string,std::shared_ptr<TextureInfo>> _textureCache;
public:
    static Director* getInstance();
    void updateScene();
    void drawScene();
    void setScene(std::shared_ptr<Scene> scene){
        _scene = scene;
    }
    std::shared_ptr<Scene> getScene(){
        return _scene;
    }
    
    void createDefaultGLPrograms();
    
    GLProgram* getGLProgram(std::string name);
    
    void addGLProgram(GLProgram* program,std::string name);
    
    bool registerTexture(std::string texKey,std::string fileName);
    
    bool unregisterTexture(std::string texKey);
    
    bool isRegisteredTexture(std::string texKey);
    
    std::shared_ptr<TextureInfo> getRegesterdTextureId(std::string texKey);
    
    void onScreenTouched(TouchInfo& touchInfo);
};

#endif /* Director_hpp */
