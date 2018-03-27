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

using namespace std;

struct Vector3
{
    float x,y,z;
};

struct PositionNormal
{
    Vector3 position;
    Vector3 normal;
};

FbxScene* InitFbxAndLoadScene(string filepath);
vector<FbxMesh*> GetMeshes(const FbxScene* scene);
vector<int> MakeIndices(const FbxMesh* mesh);
vector<Vector3> GetVertexPositions(const FbxMesh* mesh,const std::vector<int>& indices);
vector<int> MakeNormalIndices(const FbxMesh* mesh, const std::vector<int> indices);
vector<Vector3> GetNormals(const FbxMesh* mesh, const vector<int>& normalIndices);

int main(int argc, const char * argv[])
{
    cout << "Enter input file name(exclude file type)." << endl;
    string fileName;
    cin >> fileName;
    
    auto scene = InitFbxAndLoadScene(fileName + ".fbx");
    auto meshes = GetMeshes(scene);
    
    vector<PositionNormal> vertices;
    for(auto mesh : meshes)
    {
        auto indices = MakeIndices(mesh);
        auto positions = GetVertexPositions(mesh, indices);
        
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
    
    string outputFile = fileName + ".mesh";
    ofstream ofs(outputFile,ios::out | ios::binary | ios::trunc);
    ofs.write((char*)&vertices.front(), vertices.size() * sizeof(PositionNormal));
    ofs.close();
    
    return 0;
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

vector<Vector3> GetVertexPositions(const FbxMesh* mesh,const std::vector<int>& indices)
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
        positions.push_back({float(cp[0]),float(cp[1]),float(cp[2])});
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
            static_cast<float>(vNormal[0]),
            static_cast<float>(vNormal[1]),
            static_cast<float>(vNormal[2])
        });
    }
    
    return normals;
}






















