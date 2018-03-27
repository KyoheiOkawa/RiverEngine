//
//  main.cpp
//  FbxConverter
//
//  Created by 大川恭平 on 2018/03/27.
//  Copyright © 2018年 KyoheiOkawa. All rights reserved.
//

#include <iostream>
#include <string>
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

int main(int argc, const char * argv[])
{
    cout << "Enter input file path." << endl;
    string filePath;
    cin >> filePath;
    
    auto scene = InitFbxAndLoadScene(filePath);
    
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
