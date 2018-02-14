//
//  MeshResource.hpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/02/15.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#ifndef MeshResource_hpp
#define MeshResource_hpp

#include "stdinc.h"
#include "Helper.hpp"
#include "Vertex.hpp"

template <typename  T>
class MeshResource : public  ObjectInterface
{
    T* _vertex;
    
public:
    virtual ~MeshResource(){delete[] _vertex;}
    
    virtual bool init() override{return true;};

    static std::shared_ptr<MeshResource> createWithVertex(std::vector<T> vertex)
    {
        auto ret = std::shared_ptr<MeshResource<T>>(new MeshResource<T>());
        
        if(ret && ret->init())
        {
            ret->_vertex = new T[vertex.size()];
            
            for(int i = 0; i < vertex.size(); i++)
            {
                ret->_vertex[i] = vertex[i];
            }
            
            return  ret;
        }
        
        return nullptr;
    }
    
    T* GetVertexPointer()
    {
        return _vertex;
    }
};

#endif /* MeshResource_hpp */
