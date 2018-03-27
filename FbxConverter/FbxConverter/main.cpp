//
//  main.cpp
//  FbxConverter
//
//  Created by 大川恭平 on 2018/03/27.
//  Copyright © 2018年 KyoheiOkawa. All rights reserved.
//

#include <iostream>
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

int main(int argc, const char * argv[])
{
    cout << "Enter input file path." << endl;
    string filePath;
    cin >> filePath;
    
    auto scene = InitFbxAndLoadScene(filePath);
    auto meshes = GetMeshes(scene);
    
    for(auto mesh : meshes)
    {
        auto indices = MakeIndices(mesh);
        auto positions = GetVertexPositions(mesh, indices);
    }
    
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
            
//            cout << index;
//            if(j < 2)
//                cout << ", ";
        }
        
        //cout << endl;
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
        
        //cout << i << " : " << pos[0] << " : " << pos[1] << " : " << pos[2] << endl;
    }
    
    for(auto index : indices)
    {
        auto cp = controlPoints[index];
        positions.push_back({float(cp[0]),float(cp[1]),float(cp[2])});
        
        //cout << cp[0] << " : " << cp[1] << " : " << cp[2] << endl;
    }
    
    return positions;
}


























