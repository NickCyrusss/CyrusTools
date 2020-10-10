// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "EasyStyleButton.generated.h"

class USlateWidgetStyleAsset;

/**
 * 能使用简便的方式设置样式的按钮，继承于UButton
 * 除了样式设置方式不同，其它都与UButton一致
 */
UCLASS()
class CYRUSTOOLS_API UEasyStyleButton : public UButton
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Appearance Easy", meta = (AllowPrivateAccess = "true", DisplayThumbnail = "true", AllowedClasses = "Texture,MaterialInterface,SlateTextureAtlasInterface", DisallowedClasses = "MediaTexture"))
		UObject* NormalStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance Easy", meta = (AllowPrivateAccess = "true", DisplayThumbnail = "true", AllowedClasses = "Texture,MaterialInterface,SlateTextureAtlasInterface", DisallowedClasses = "MediaTexture"))
		UObject* HoveredStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance Easy", meta = (AllowPrivateAccess = "true", DisplayThumbnail = "true", AllowedClasses = "Texture,MaterialInterface,SlateTextureAtlasInterface", DisallowedClasses = "MediaTexture"))
		UObject* PressedStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance Easy", meta = (sRGB = "true"))
		FLinearColor HoveredColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, Category = "Appearance Easy", meta = (sRGB = "true"))
		FLinearColor PressedColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, Category = "Appearance Easy", meta = (DisplayName = "Size"))
		FVector2D ButtonSize = FVector2D(SlateBrushDefs::DefaultImageSize, SlateBrushDefs::DefaultImageSize);
public:

	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
};
