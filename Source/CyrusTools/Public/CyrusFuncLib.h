// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../../../../RuntimeMeshComponent/Source/RuntimeMeshComponent/Public/RuntimeMeshCore.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CyrusFuncLib.generated.h"

USTRUCT(BlueprintType)
struct FMeshInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    TArray<FVector> Vertices;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    TArray<int32> Triangles;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    TArray<FVector> Normals;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    TArray<FVector2D> UV0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    TArray<FLinearColor> VertexColors;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    TArray<FRuntimeMeshTangent> Tangents;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    FTransform RelativeTransform;
};

USTRUCT(BlueprintType)
struct FMeshReturnedData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    bool bSuccess = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    int32 NumMeshes = 0;


    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
    TArray<FMeshInfo> MeshInfo;
};

UCLASS()
class CYRUSTOOLS_API UCyrusFuncLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:

    UFUNCTION(BlueprintCallable, Category="CyrusTools")
    static class ARuntimeMeshActor* LoadMeshFromDisk(const FTransform& spawnTransform);
    
    UFUNCTION(BlueprintCallable, Category="CyrusTools")
    static bool LoadMesh(const FString& filePath, FMeshReturnedData& outMeshData);

    UFUNCTION(BlueprintCallable, Category="CyrusTools")
    static FString SelectFileOnDisk();
};
