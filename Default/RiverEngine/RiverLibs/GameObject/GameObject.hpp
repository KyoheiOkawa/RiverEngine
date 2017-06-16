//
//  GameObject.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <new>
#include <memory>
#include <map>
#include <typeindex>
#include <list>

class Component;

class GameObject : public ObjectInterface,public ShapeInterface
{
protected:
    std::map<std::type_index,std::shared_ptr<Component>> _compMap;
    std::list<std::type_index> _compOrder;
private:
    std::shared_ptr<Component> searchComponent(std::type_index typeId)const;
    
    void addMakedComponent(std::type_index typeId, const std::shared_ptr<Component>& ptr);
public:
    GameObject();
    
    virtual ~GameObject();
    
    template<typename T,typename... Ts>
    std::shared_ptr<T> addComponent(Ts&&... params){
        auto ptr = searchComponent(std::type_index(typeid(T)));
        
        if(ptr){
            auto retPtr = std::dynamic_pointer_cast<T>(ptr);
            if(retPtr){
                return retPtr;
            }
            else{
                //すでにコンポーネントがありましたが、型キャストできません
                assert(false);
            }
        }
        else{
            std::shared_ptr<T> newPtr = ObjectFactory::create<T>(getThis<GameObject>(),params...);
            addMakedComponent(std::type_index(typeid(T)), newPtr);
            return newPtr;
        }
    }

    static std::shared_ptr<GameObject> create();
    
    virtual bool init(){ return true;};
    
    virtual void update(){};
    
    virtual void draw(){};
};



#endif /* GameObject_hpp */
