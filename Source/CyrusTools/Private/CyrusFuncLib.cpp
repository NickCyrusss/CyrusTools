// Fill out your copyright notice in the Description page of Project Settings.


#include "CyrusFuncLib.h"

#include "DesktopPlatformModule.h"
#include "RuntimeMeshActor.h"
#include "Providers/RuntimeMeshProviderStatic.h"
#include "assimp/Importer.hpp"  // C++ importer interface
#include "assimp/scene.h"       // Output data structure
#include "assimp/postprocess.h" // Post processing flags

void FindMeshInfo(const aiScene* scene, aiNode* node, FMeshReturnedData& result)
{
    for (uint32 i = 0; i < node->mNumMeshes; i++)
    {
        std::string TestString = node->mName.C_Str();
        FString fs = FString(TestString.c_str());
        UE_LOG(LogTemp, Warning, TEXT("FindMeshInfo. %s\n"), *fs);
        const int meshidx = *node->mMeshes;
        aiMesh* mesh = scene->mMeshes[meshidx];
        FMeshInfo& mi = result.MeshInfo[meshidx];

        //transform.
        const aiMatrix4x4 tempTrans = node->mTransformation;
        FMatrix tempMatrix;
        tempMatrix.M[0][0] = tempTrans.a1;
        tempMatrix.M[0][1] = tempTrans.b1;
        tempMatrix.M[0][2] = tempTrans.c1;
        tempMatrix.M[0][3] = tempTrans.d1;
        tempMatrix.M[1][0] = tempTrans.a2;
        tempMatrix.M[1][1] = tempTrans.b2;
        tempMatrix.M[1][2] = tempTrans.c2;
        tempMatrix.M[1][3] = tempTrans.d2;
        tempMatrix.M[2][0] = tempTrans.a3;
        tempMatrix.M[2][1] = tempTrans.b3;
        tempMatrix.M[2][2] = tempTrans.c3;
        tempMatrix.M[2][3] = tempTrans.d3;
        tempMatrix.M[3][0] = tempTrans.a4;
        tempMatrix.M[3][1] = tempTrans.b4;
        tempMatrix.M[3][2] = tempTrans.c4;
        tempMatrix.M[3][3] = tempTrans.d4;
        mi.RelativeTransform = FTransform(tempMatrix);

        //vet
        for (uint32 j = 0; j < mesh->mNumVertices; ++j)
        {
            FVector vertex = FVector(
                mesh->mVertices[j].x,
                mesh->mVertices[j].y,
                mesh->mVertices[j].z/100);

            vertex = mi.RelativeTransform.TransformFVector4(vertex);
            mi.Vertices.Push(vertex);

            //Normal
            if (mesh->HasNormals())
            {
                FVector normal = FVector(
                    mesh->mNormals[j].x,
                    mesh->mNormals[j].y,
                    mesh->mNormals[j].z);

                //normal = mi.RelativeTransform.TransformFVector4(normal);
                mi.Normals.Push(normal);
            }
            else
            {
                mi.Normals.Push(FVector::ZeroVector);
            }

            //UV Coordinates - inconsistent coordinates
            if (mesh->HasTextureCoords(0))
            {
                FVector2D uv = FVector2D(mesh->mTextureCoords[0][j].x, -mesh->mTextureCoords[0][j].y);
                mi.UV0.Add(uv);
            }

            //Tangent
            if (mesh->HasTangentsAndBitangents())
            {
                FRuntimeMeshTangent meshTangent = FRuntimeMeshTangent(
                    mesh->mTangents[j].x,
                    mesh->mTangents[j].y,
                    mesh->mTangents[j].z
                );
                mi.Tangents.Push(meshTangent);
            }

            //Vertex color
            if (mesh->HasVertexColors(0))
            {
                FLinearColor color = FLinearColor(
                    mesh->mColors[0][j].r,
                    mesh->mColors[0][j].g,
                    mesh->mColors[0][j].b,
                    mesh->mColors[0][j].a
                );
                mi.VertexColors.Push(color);
            }
        }
    }
}


void FindMesh(const aiScene* scene, aiNode* node, FMeshReturnedData& retdata)
{
    FindMeshInfo(scene, node, retdata);

    for (uint32 m = 0; m < node->mNumChildren; ++m)
    {
        FindMesh(scene, node->mChildren[m], retdata);
    }
}

ARuntimeMeshActor* UCyrusFuncLib::LoadMeshFromDisk(const FTransform& spawnTransform)
{
    const FString filePath = SelectFileOnDisk();
    if (filePath.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("filepath is empty.\n"));
        return nullptr;
    }
    FMeshReturnedData result;
    if (LoadMesh(filePath, result) && GWorld)
    {
        ARuntimeMeshActor* rmcActor = GWorld->SpawnActor<ARuntimeMeshActor>(ARuntimeMeshActor::StaticClass(), spawnTransform);
        URuntimeMeshProviderStatic* StaticProvider = NewObject<URuntimeMeshProviderStatic>();
        rmcActor->GetRuntimeMeshComponent()->Initialize(StaticProvider);
        rmcActor->SetRuntimeMeshMobility(ERuntimeMeshMobility::Movable);

        for (int32 index = 0; index < result.MeshInfo.Num(); index++)
        {
            StaticProvider->CreateSectionFromComponents(0,
                                                        index,
                                                        index,
                                                        result.MeshInfo[index].Vertices,
                                                        result.MeshInfo[index].Triangles,
                                                        result.MeshInfo[index].Normals,
                                                        result.MeshInfo[index].UV0,
                                                        result.MeshInfo[index].VertexColors,
                                                        result.MeshInfo[index].Tangents);
            StaticProvider->SetupMaterialSlot(index, FName("Cube Base"), UMaterial::GetDefaultMaterial(MD_Surface));
            //StaticProvider->UpdateSection(0, index, StaticProvider->GetSectionRenderData(0, index));
        }
        return rmcActor;
    }
    else
    {
        return nullptr;
    }
}

bool UCyrusFuncLib::LoadMesh(const FString& filePath, FMeshReturnedData& outMeshData)
{
    const std::string file = TCHAR_TO_UTF8(*filePath);

    Assimp::Importer assImporter;

    const aiScene* mScenePtr = assImporter.ReadFile(
        file, 0/*aiProcess_Triangulate | aiProcess_MakeLeftHanded | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes*/);

    if (mScenePtr == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Runtime Mesh Loader: Read mesh file failure.\n"));
        return false;
    }

    if (mScenePtr->HasMeshes())
    {
        outMeshData.MeshInfo.SetNum(mScenePtr->mNumMeshes, false);

        FindMesh(mScenePtr, mScenePtr->mRootNode, outMeshData);

        for (uint32 i = 0; i < mScenePtr->mNumMeshes; ++i)
        {
            //Triangle number
            for (uint32 l = 0; l < mScenePtr->mMeshes[i]->mNumFaces; ++l)
            {
                for (uint32 m = 0; m < mScenePtr->mMeshes[i]->mFaces[l].mNumIndices; ++m)
                {
                    outMeshData.MeshInfo[i].Triangles.Push(mScenePtr->mMeshes[i]->mFaces[l].mIndices[m]);
                }
            }
        }
        outMeshData.bSuccess = true;
    }
    return true;
}

FString UCyrusFuncLib::SelectFileOnDisk()
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        TArray<FString> OpenFilenames;
        DesktopPlatform->OpenFileDialog(
            nullptr,
            TEXT("OpenFile"),
            FString(TEXT("")),
            TEXT(""),
            TEXT("All Files (*.*)"),
            EFileDialogFlags::None,
            OpenFilenames
        );

        if (OpenFilenames.Num() > 0)
        {
            return FPaths::ConvertRelativePathToFull(OpenFilenames[0]);
        }
    }
    return TEXT("");
}
