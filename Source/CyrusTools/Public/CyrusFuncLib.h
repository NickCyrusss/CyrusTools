// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CyrusFuncLib.generated.h"


UCLASS()
class CYRUSTOOLS_API UCyrusFuncLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:

    //UFUNCTION(BlueprintCallable, Category="CyrusTools")
    //static FString SelectFileOnDisk();

	UFUNCTION(BlueprintCallable, Category = "CyrusTools")
		static void CreateWindow(FText inWindowTitle, UUserWidget* inWidget, FVector2D inSize);

	UFUNCTION(BlueprintCallable, Category = "CyrusTools")
		static void DestroyWindow();

	UFUNCTION(BlueprintCallable, Category = "CyrusTools")
		static void CreateProcess(FString fileName);

private:
	static TSharedPtr<class SWindow> CreationWindow;


};
