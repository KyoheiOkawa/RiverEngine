//
//  main.cpp
//  FbxConverter
//
//  Created by 大川恭平 on 2018/03/27.
//  Copyright © 2018年 KyoheiOkawa. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fbxsdk.h>

#include <OpenGL/OpenGL.h>

using namespace std;

struct Vector2
{
    GLfloat x,y;
};

struct Vector3
{
    GLfloat x,y,z;
};

struct PositionNormal
{
    Vector3 position;
    Vector3 normal;
};

struct PositionNormalTexture
{
    Vector3 position;
    Vector3 normal;
    Vector2 uv;
};

FbxScene* InitFbxAndLoadScene(string filepath);
vector<FbxMesh*> GetMeshes(const FbxScene* scene);
vector<int> MakeIndices(const FbxMesh* mesh);
vector<Vector3> GetVertexPositions(const FbxMesh* mesh,const std::vector<int>& indices, const float scale);
vector<int> MakeNormalIndices(const FbxMesh* mesh, const std::vector<int> indices);
vector<Vector3> GetNormals(const FbxMesh* mesh, const vector<int>& normalIndices);
vector<int> MakeUVIndices(const FbxMesh* mesh, const std::vector<int> indices);
vector<Vector2> GetUVs(const FbxMesh* mesh, const std::vector<int> indices);

vector<PositionNormal> GetPositionNormal(vector<FbxMesh*> meshes,const float scale = 1.0f);
vector<PositionNormalTexture> GetPositionNormalTexture(vector<FbxMesh*> meshes,const float scale = 1.0f);

template <typename T>
void SaveBinary(string fileName,vector<T> vertices);

int main(int argc, const char * argv[])
{
    cout << "Choose vertex type(pn or pnt)." << endl;
    string vertexType;
    cin >> vertexType;
    
    cout << "Enter input file name(exclude file type)." << endl;
    string fileName;
    cin >> fileName;
    
    cout << "Enter model scale(default 1.0)." << endl;
    float scale;
    cin >> scale;
    
    auto scene = InitFbxAndLoadScene(fileName + ".fbx");
    auto meshes = GetMeshes(scene);
    
    if(vertexType == "pn")
    {
        vector<PositionNormal> vertices = GetPositionNormal(meshes,scale);
        SaveBinary(fileName, vertices);
    }
    else if(vertexType == "pnt")
    {
        vector<PositionNormalTexture> vertices = GetPositionNormalTexture(meshes,scale);
        SaveBinary(fileName, vertices);
    }
    
    return 0;
}

vector<PositionNormal> GetPositionNormal(vector<FbxMesh*> meshes,const float scale)
{
    vector<PositionNormal> vertices;
    for(auto mesh : meshes)
    {
        auto indices = MakeIndices(mesh);
        auto positions = GetVertexPositions(mesh, indices,scale);
        
        auto normalIndices = MakeNormalIndices(mesh, indices);
        auto normals = GetNormals(mesh, normalIndices);
        
        int size = indices.size();
        for(int i = 0; i < size; i++)
        {
            vertices.push_back({positions[i],normals[i]});
            
            printf("%04d : %+f, %+f, %+f",i,positions[i].x,positions[i].y,positions[i].z);
            printf(" / %+f, %+f, %+f\n",normals[i].x,normals[i].y,normals[i].z);
        }
    }
    
    return vertices;
}

vector<PositionNormalTexture> GetPositionNormalTexture(vector<FbxMesh*> meshes,const float scale)
{
    vector<PositionNormalTexture> vertices;
    for(auto mesh : meshes)
    {
        auto indices = MakeIndices(mesh);
        auto positions = GetVertexPositions(mesh, indices,scale);
        
        auto normalIndices = MakeNormalIndices(mesh, indices);
        auto normals = GetNormals(mesh, normalIndices);
        
        auto uvIndices = MakeUVIndices(mesh, indices);
        auto uvs = GetUVs(mesh,uvIndices);
        
        int size = indices.size();
        for(int i = 0; i < size; i++)
        {
            vertices.push_back({positions[i],normals[i],uvs[i]});
            
            printf("%04d : %+f, %+f, %+f",i,positions[i].x,positions[i].y,positions[i].z);
            printf(" / %+f, %+f, %+f",normals[i].x,normals[i].y,normals[i].z);
            printf(" / %+f, %+f\n",uvs[i].x,uvs[i].y);
        }
    }
    
    return vertices;
}

template <typename T>
void SaveBinary(string fileName,vector<T> vertices)
{
    string outputFile = fileName + ".mesh";
    ofstream ofs(outputFile,ios::out | ios::binary | ios::trunc);
    ofs.write((char*)&vertices.front(), vertices.size() * sizeof(T));
    ofs.close();
}

FbxScene* InitFbxAndLoadScene(string filePath)
{
    auto fbxManager = FbxManager::Create();
    if(fbxManager)
        cout << "FbxManager create succeeded." << endl;
    else
        cout << "FbxManager create failed." << endl;
    
    auto fbxIOSettings = FbxIOSettings::Create(fbxManager, IOSROOT);
    if(fbxIOSettings)
        cout << "fbxIOSettings create succeeded." << endl;
    else
        cout << "FbxIOSettings create failed." << endl;
    
    fbxManager->SetIOSettings(fbxIOSettings);
    
    auto fbxImporter = FbxImporter::Create(fbxManager, "");
    if(fbxImporter)
        cout << "FbxImporter create succeeded." << endl;
    else
        cout << "FbxImporter create failed." << endl;
    
    bool bInitialize = fbxImporter->Initialize(filePath.c_str(),-1,fbxManager->GetIOSettings());
    if(bInitialize)
        cout << "FbxImporter initialize succeeded." << endl;
    else
        cout << "FbxImporter initialize failed." << endl;
    
    auto scene = FbxScene::Create(fbxManager, "myScene");
    if(scene)
        cout << "FbxScene create succeeded." << endl;
    else
        cout << "FbxScene create failed." << endl;
    
    bool bImport = fbxImporter->Import(scene);
    if(bImport)
        cout << "Import scene succeeded." << endl;
    else
        cout << "Import scene failed." << endl;
    
    fbxImporter->Destroy();
    
    FbxGeometryConverter fbxGeometryConverter(fbxManager);
    bool bTriangulate = fbxGeometryConverter.Triangulate(scene, true);
    if(bTriangulate)
        cout << "Triangulate succeeded." << endl;
    else
        cout << "Triangulate failed." << endl;
    
    return scene;
}

vector<FbxMesh*> GetMeshes(const FbxScene* scene)
{
    vector<FbxMesh*> meshes;
    
    int numMeshes = scene->GetMemberCount<FbxMesh>();
    cout << "Meshes : " << numMeshes << endl;
    
    for(int i = 0; i < numMeshes; i++)
    {
        auto mesh = scene->GetMember<FbxMesh>(i);
        meshes.push_back(mesh);
    }
    
    return meshes;
}

vector<int> MakeIndices(const FbxMesh* mesh)
{
    std::vector<int> indices;
    
    auto numPolygon = mesh->GetPolygonCount();
    
    indices.reserve(numPolygon * 3);
    for(int i = 0; i < numPolygon; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            auto index = mesh->GetPolygonVertex(i, j);
            indices.push_back(index);
        }
    }
    
    return indices;
}

vector<Vector3> GetVertexPositions(const FbxMesh* mesh,const std::vector<int>& indices,const float scale)
{
    vector<Vector3> positions;
    
    auto numControlPoint = mesh->GetControlPointsCount();
    cout << "ControlPoint Count : " << numControlPoint << endl;
    
    vector<FbxVector4> controlPoints;
    controlPoints.reserve(numControlPoint);
    for(int i = 0; i < numControlPoint; i++)
    {
        auto pos = mesh->GetControlPointAt(i);
        controlPoints.push_back(pos);
    }
    
    for(auto index : indices)
    {
        auto cp = controlPoints[index];
        positions.push_back({GLfloat(cp[0] * scale),GLfloat(cp[1] * scale),GLfloat(cp[2] * scale)});
    }
    
    return positions;
}

vector<int> MakeNormalIndices(const FbxMesh* mesh, const std::vector<int> indices)
{
    vector<int> normalIndices;
    
    auto element = mesh->GetElementNormal();
    
    switch(element->GetMappingMode())
    {
        case FbxGeometryElement::eByControlPoint:
            normalIndices = indices;
            break;
        case FbxGeometryElement::eByPolygonVertex:
        {
            int index = 0;
            
            auto numPolygons = mesh->GetPolygonCount();
            for(int i = 0; i < numPolygons; i++)
            {
                auto numVertices = mesh->GetPolygonSize(i);
                for(int j = 0; j < numVertices; j++)
                {
                    normalIndices.push_back(index++);
                }
            }
            
            break;
        }
    }
    
    return normalIndices;
}

vector<Vector3> GetNormals(const FbxMesh* mesh, const vector<int>& normalIndices)
{
    vector<Vector3> normals;
    
    auto element = mesh->GetElementNormal();
    for(auto index : normalIndices)
    {
        FbxVector4 vNormal;
        
        switch(element->GetReferenceMode())
        {
            case FbxGeometryElement::eDirect:
                vNormal = element->GetDirectArray().GetAt(index);
                break;
            case FbxGeometryElement::eIndexToDirect:
                vNormal = element->GetDirectArray().GetAt(element->GetIndexArray().GetAt(index));
                break;
        }
        
        normals.push_back({
            static_cast<GLfloat>(vNormal[0]),
            static_cast<GLfloat>(vNormal[1]),
            static_cast<GLfloat>(vNormal[2])
        });
    }
    
    return normals;
}

vector<int> MakeUVIndices(const FbxMesh* mesh, const std::vector<int> indices)
{
    vector<int> uvIndices;
    
    auto element = mesh->GetElementUV();
    
    switch(element->GetMappingMode())
    {
        case FbxLayerElement::eByControlPoint:
            uvIndices = indices;
            break;
        case FbxLayerElement::eByPolygonVertex:
        {
            int index = 0;
            
            auto numPolygons = mesh->GetPolygonCount();
            for(int i = 0; i < numPolygons; i++)
            {
                auto numVertices = mesh->GetPolygonSize(i);
                for(int j = 0; j < numVertices; j++)
                {
                    uvIndices.push_back(index++);
                }
            }
            
            break;
        }
    }
    
    return uvIndices;
}

vector<Vector2> GetUVs(const FbxMesh* mesh,const std::vector<int> indices)
{
    vector<Vector2> uvVec;
    
    int layerCount = mesh->GetLayerCount();
    for(int i = 0; i < layerCount; i++)
    {
        auto layer = mesh->GetLayer(i);
        auto elem = layer->GetUVs();
        if(elem == 0)
            continue;
        
        for(auto index : indices)
        {
            FbxVector2 uv;
            
            switch (elem->GetReferenceMode())
            {
                case FbxLayerElement::eDirect:
                    uv = elem->GetDirectArray().GetAt(index);
                    break;
                case FbxLayerElement::eIndexToDirect:
                    uv = elem->GetDirectArray().GetAt(elem->GetIndexArray().GetAt(index));
                    break;
            }
            
            uvVec.push_back({
                static_cast<GLfloat>(uv[0]),
                static_cast<GLfloat>(uv[1])
            });
        }
        
        break;
    }
    
    return uvVec;
}




















