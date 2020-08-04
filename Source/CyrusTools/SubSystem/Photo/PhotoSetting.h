// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhotoSetting.generated.h"

USTRUCT(BlueprintType)
struct FPhotoSubSystemSettingStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		FString LocalCachePath;
};
