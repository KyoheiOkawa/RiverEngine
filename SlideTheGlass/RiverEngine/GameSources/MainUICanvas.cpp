//
//  MainUICanvas.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/24.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "MainUICanvas.hpp"

MainUICanvas::MainUICanvas()
{
    
}

shared_ptr<MainUICanvas> MainUICanvas::create()
{
    shared_ptr<MainUICanvas> ret(new MainUICanvas());
    
    if(ret && ret->init())
    {
        return ret;
    }
    
    return nullptr;
}

bool MainUICanvas::init()
{
    GameObject::init();
    
    float width = Application::getInstance()->getSurfaceWidth();
    float height = Application::getInstance()->getSurfaceHeight();
    
    _rankButton = Sprite::createWithTexture("RANK_UI");
    _rankButton->getTransform()->setPosition(Vector3(width - 82.0f,82.0f,0.0f));
    
    return true;
}

void MainUICanvas::update()
{
    
}

void MainUICanvas::draw()
{
    _rankButton->draw();
}

void MainUICanvas::onScreenTouched(TouchInfo& info)
{
    Vector2 point;
    point.x = info.posX;
    point.y = info.posY;
    
    auto btTrans = _rankButton->getTransform();
    
    Vector2 btPos;
    btPos.x = btTrans->getPosition().x;
    btPos.y = btTrans->getPosition().y;
    
    switch (info.type)
    {
        case TouchType::BEGAN:
        {
            if(isInPoint(point, btPos, _rankButton->getSpriteSize()))
                btTrans->setScale(Vector3(1.25f,1.25f,1.25f));
            break;
        }
        case TouchType::MOVED:
        {
            if(!isInPoint(point, btPos, _rankButton->getSpriteSize()))
                btTrans->setScale(Vector3(1.0f,1.0f,1.0f));
            
            break;
        }
        case TouchType::ENDED:
        {
            btTrans->setScale(Vector3(1.0f,1.0f,1.0f));
            break;
        }
    }
}

bool MainUICanvas::isInPoint(Vector2 point, Vector2 otherPoint, Vector2 otherSize)
{
    Vector2 halfSize;
    halfSize.x = otherSize.x / 2.0f;
    halfSize.y = otherSize.y / 2.0f;
    
    if((point.x >= otherPoint.x - halfSize.x) && (point.x <= otherPoint.x + halfSize.x))
    {
        if((point.y >= otherPoint.y - halfSize.y) && (point.y <= otherPoint.y + halfSize.y))
        {
            return true;
        }
    }
    
    return false;
}
