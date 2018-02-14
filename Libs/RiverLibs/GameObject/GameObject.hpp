//
//  GameObject.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2017/06/01.
//  Copyright © 2017年 BiGRiVER. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "stdinc.h"

class Component;
class Transform;

class GameObject : public ObjectInterface,public ShapeInterface
{
protected:
    std::shared_ptr<Scene> _scene;
    std::map<std::type_index,std::shared_ptr<Component>> _compMap;
    std::list<std::type_index> _compOrder;
    std::shared_ptr<Transform> _transform;
    int _drawLayer = 0;
private:
    std::shared_ptr<Component> searchComponent(std::type_index typeId)const;
    
    void addMakedComponent(std::type_index typeId, const std::shared_ptr<Component>& ptr);
public:
    GameObject();
    
    virtual ~GameObject();
    
    
    std::shared_ptr<Transform> getTransform(){
        return _transform;
    }
    
    void setTransform(const std::shared_ptr<Transform>& ptr);
    
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
    
    template<typename T>
    std::shared_ptr<T> getComponent(bool exceptionActive = true) const{
        auto ptr = searchComponent(std::type_index(typeid(T)));
        if(ptr){
            auto retPtr = std::dynamic_pointer_cast<T>(ptr);
            
            //コンポーネントはありましたが。
            //指定の方にキャストできませんでした。
            assert(retPtr);
            
            return retPtr;
        }
        else{
            if(exceptionActive){
                //コンポーネントが見つかりません
                assert(false);
            }
        }
        
        return nullptr;
    }
    
    void setScene(std::shared_ptr<Scene> scene){
        _scene = scene;
    }
    
    std::shared_ptr<Scene> getScene(){
        return _scene;
    }
    
    void setDrawLayer(int layer){
        _drawLayer = layer;
    }
    
    int getDrawLayer(){
        return _drawLayer;
    }

    static std::shared_ptr<GameObject> create();
    
    virtual bool init();
    
    void componentUpdate();
    virtual void update(){};
    
    void componentDraw();
    virtual void draw(){};
    
    virtual void onScreenTouched(TouchInfo& touchInfo){};
};



#endif /* GameObject_hpp */
