//
//  NumberSprite.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/10.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "NumberSprite.hpp"

NumberSprite::NumberSprite()
{
    
}

NumberSprite::~NumberSprite()
{
    
}

std::shared_ptr<NumberSprite> NumberSprite::create(string texKey,unsigned int number)
{
    auto ret = std::shared_ptr<NumberSprite>(new NumberSprite());
    ret->_texKey = texKey;
    ret->_number = number;
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool NumberSprite::init()
{
    if(!GameObject::init())
        return false;
    
    auto transPtr = getTransform();

    auto director = Director::getInstance();
    _useProgram = director->getGLProgram("PTSprite");
    
    _attr_pos = _useProgram->getAttribLocation("attr_pos");
    _attr_uv = _useProgram->getAttribLocation("attr_uv");
    _unif_matrix = _useProgram->getUnifLocation("unif_matrix");
    _unif_texture = _useProgram->getUnifLocation("unif_texture");
    
    auto texInfo = Director::getInstance()->getRegesterdTextureInfo(_texKey);
    _texture_id = texInfo->id;
    _spriteSize.x = texInfo->height;
    _spriteSize.y = texInfo->height;
    
    unsigned int digit = MyUtil::getDigit(_number);
    vector<int> eachNumbers = MyUtil::extractTotalDigitsSpotCount(_number, digit);
    bool isEven = (digit % 2 == 0);
    std::vector<PositionTexture> vertex;
    if(!isEven)
    {
        unsigned int centerIndex = calcOddCenterIndex(digit);
        vertex.push_back({{-0.5f,0.5f},{eachNumbers[centerIndex] * 0.1f,0.0f}});
        vertex.push_back({{-0.5f,-0.5f},{eachNumbers[centerIndex] * 0.1f,1.0f}});
        vertex.push_back({{0.5f,0.5f},{(eachNumbers[centerIndex] + 1) * 0.1f,0.0f}});
        vertex.push_back({{0.5f,0.5f},{(eachNumbers[centerIndex] + 1) * 0.1f,0.0f}});
        vertex.push_back({{-0.5f,-0.5f},{eachNumbers[centerIndex] * 0.1f,1.0f}});
        vertex.push_back({{0.5f,-0.5f},{(eachNumbers[centerIndex] + 1) * 0.1f,1.0f}});
        
        if(digit > 0)
        {
            unsigned int half = (digit - 1) / 2.0f;
            //右
            for(int i = 0; i < half; i++)
            {
                unsigned int plusI = i + 1;
                float diff = plusI;
                vertex.push_back({{-0.5f+diff,0.5f},{eachNumbers[centerIndex-plusI] * 0.1f,0.0f}});
                vertex.push_back({{-0.5f+diff,-0.5f},{eachNumbers[centerIndex-plusI] * 0.1f,1.0f}});
                vertex.push_back({{0.5f+diff,0.5f},{(eachNumbers[centerIndex-plusI] + 1) * 0.1f,0.0f}});
                vertex.push_back({{0.5f+diff,0.5f},{(eachNumbers[centerIndex-plusI] + 1) * 0.1f,0.0f}});
                vertex.push_back({{-0.5f+diff,-0.5f},{eachNumbers[centerIndex-plusI] * 0.1f,1.0f}});
                vertex.push_back({{0.5f+diff,-0.5f},{(eachNumbers[centerIndex-plusI] + 1) * 0.1f,1.0f}});
            }
            //左
            for(int i = 0; i < half; i++)
            {
                unsigned int plusI = i + 1;
                float diff = plusI;
                vertex.push_back({{-0.5f-diff,0.5f},{eachNumbers[centerIndex+plusI] * 0.1f,0.0f}});
                vertex.push_back({{-0.5f-diff,-0.5f},{eachNumbers[centerIndex+plusI] * 0.1f,1.0f}});
                vertex.push_back({{0.5f-diff,0.5f},{(eachNumbers[centerIndex+plusI] + 1) * 0.1f,0.0f}});
                vertex.push_back({{0.5f-diff,0.5f},{(eachNumbers[centerIndex+plusI] + 1) * 0.1f,0.0f}});
                vertex.push_back({{-0.5f-diff,-0.5f},{eachNumbers[centerIndex+plusI] * 0.1f,1.0f}});
                vertex.push_back({{0.5f-diff,-0.5f},{(eachNumbers[centerIndex+plusI] + 1) * 0.1f,1.0f}});
            }
        }
    }
    else
    {
        float startX = -(float)digit / 2.0f;
        for(int i = 0; i < digit; i++)
        {
            float diff = i;
            unsigned numIndex = (digit-1)-i;
            vertex.push_back({{startX+diff,0.5f},{eachNumbers[numIndex] * 0.1f,0.0f}});
            vertex.push_back({{startX+diff,-0.5f},{eachNumbers[numIndex] * 0.1f,1.0f}});
            vertex.push_back({{(startX+1.0f)+diff,0.5f},{(eachNumbers[numIndex] + 1) * 0.1f,0.0f}});
            vertex.push_back({{(startX+1.0f)+diff,0.5f},{(eachNumbers[numIndex] + 1) * 0.1f,0.0f}});
            vertex.push_back({{startX+diff,-0.5f},{eachNumbers[numIndex] * 0.1f,1.0f}});
            vertex.push_back({{(startX+1.0f)+diff,-0.5f},{(eachNumbers[numIndex] + 1) * 0.1f,1.0f}});
        }
    }
    
    _meshResource = MeshResource<PositionTexture>::createWithVertex(vertex);
    
    return true;
}

void NumberSprite::update()
{
    
}

void NumberSprite::draw()
{
    _useProgram->use();
    glEnableVertexAttribArray(_attr_pos);
    glEnableVertexAttribArray(_attr_uv);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glVertexAttribPointer(_attr_pos, 2, GL_FLOAT, GL_FALSE, sizeof(PositionTexture), (GLvoid*)_meshResource->GetVertexPointer());
    glVertexAttribPointer(_attr_uv, 2, GL_FLOAT, GL_FALSE, sizeof(PositionTexture), (GLvoid*)((GLubyte*)_meshResource->GetVertexPointer() + sizeof(GLfloat)*3));
    
    auto app = Application::getInstance();
    
    auto trans = getTransform();
    auto pos = trans->getPosition();
    auto scale = trans->getScale();
    auto rotation = trans->getRotation();
    
    Vector3 pivot = trans->getPivot();
    
    Matrix4x4 matrix = Matrix4x4::create2DAffine(pos, _spriteSize , scale, rotation.z, Vector2(app->getSurfaceWidth(),app->getSurfaceHeight()), pivot);
    
    glUniformMatrix4fv(_unif_matrix, 1, GL_FALSE, matrix.matrix);
    glUniform1i(_unif_texture, 0);
    
    glBindTexture(GL_TEXTURE_2D, _texture_id);
    glDrawArrays(GL_TRIANGLES, 0, _meshResource->GetVertexCount());
    
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(_attr_pos);
    glDisableVertexAttribArray(_attr_uv);
}
