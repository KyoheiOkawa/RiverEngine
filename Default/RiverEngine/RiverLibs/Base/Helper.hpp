//
//  Helper.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/11.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef Helper_hpp
#define Helper_hpp

#include <stdio.h>
#include <memory>
#include <assert.h>

class ObjectInterface : public std::enable_shared_from_this<ObjectInterface>
{
protected:
    ObjectInterface(){}
    
    virtual ~ObjectInterface(){}
    
public:
    template<typename T>
    std::shared_ptr<T> getThis(){
        auto ptr = std::dynamic_pointer_cast<T>(shared_from_this());
        
        assert(ptr);//キャストできません
        
        return ptr;
    }
    
    virtual bool init() = 0;
private:
    //コピー禁止
    ObjectInterface(const ObjectInterface&) = delete;
    ObjectInterface& operator=(const ObjectInterface&) = delete;
    //ムーブ禁止
    ObjectInterface(const ObjectInterface&&) = delete;
    ObjectInterface& operator=(const ObjectInterface&&) = delete;
};

class ShapeInterface
{
public:
    
    ShapeInterface(){}
    
    virtual ~ShapeInterface(){}
    
    virtual void update() = 0;
    
    virtual void draw() = 0;
    
private:
    //コピー禁止
    ShapeInterface(const ShapeInterface&) = delete;
    ShapeInterface& operator=(const ShapeInterface&) = delete;
    //ムーブ禁止
    ShapeInterface(const ShapeInterface&&) = delete;
    ShapeInterface& operator=(const ShapeInterface&&) = delete;
};

class ObjectFactory
{
public:
    template<typename T,typename... Ts>
    static std::shared_ptr<T> create(Ts&&... params){
        std::shared_ptr<T> ptr = std::shared_ptr<T>(new T(params...));
        
        ptr->init();
        
        return ptr;
    }
};

#endif /* Helper_hpp */
