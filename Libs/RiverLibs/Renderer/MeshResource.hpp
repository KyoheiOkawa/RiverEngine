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
#include "FileUtils.hpp"

template <typename  T>
class MeshResource : public  ObjectInterface
{
    size_t _vertexCount;
    unique_ptr<T[]> _vertex;
    
public:
    virtual ~MeshResource()
    {
        _vertex.release();
    }
    
    virtual bool init() override{return true;};

    static std::shared_ptr<MeshResource> createWithVertex(std::vector<T> vertex)
    {
        auto ret = std::shared_ptr<MeshResource<T>>(new MeshResource<T>());
        
        if(ret && ret->init())
        {
            ret->_vertex.reset(new T[vertex.size()]);
            ret->_vertexCount = vertex.size();
            
            for(int i = 0; i < vertex.size(); i++)
            {
                ret->_vertex[i] = vertex[i];
            }
            
            return  ret;
        }
        
        return nullptr;
    }
    
    static std::shared_ptr<MeshResource> createWithFile(const std::string fileName)
    {
        auto ret = std::shared_ptr<MeshResource<T>>(new MeshResource<T>());
        
        if(ret && ret->init())
        {
            unique_ptr<char[]> meshData;
            size_t size = FileUtils::getInstance()->loadBinary(fileName,"mesh",meshData);
            ret->_vertexCount = size / sizeof(T);
            
            ret->_vertex.reset((T*)meshData.get());
            meshData.release();
            
            return ret;
        }
        
        return nullptr;
    }
    
    T* GetVertexPointer()
    {
        return _vertex.get();
    }
    
    size_t GetVertexCount()
    {
        return _vertexCount;
    }
};

#endif /* MeshResource_hpp */
