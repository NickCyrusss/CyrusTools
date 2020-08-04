// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PhotoSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FGetPhotoDelegate, FString, id, UTexture2D*, Texture);

UCLASS()
class CYRUSTOOLS_API UPhotoSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "PhotoSubsystem")
		void GetPhotoByURL(const FString& url, FGetPhotoDelegate FinishDelegate);

private:

	void DownloadPhoto(const FString& url);
	
public:

};
