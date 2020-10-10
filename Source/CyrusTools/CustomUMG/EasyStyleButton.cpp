// Fill out your copyright notice in the Description page of Project Settings.


#include "EasyStyleButton.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SButton.h"
#include "Components/ButtonSlot.h"


#define LOCTEXT_NAMESPACE "UMG"

void UEasyStyleButton::SynchronizeProperties()
{
	FButtonStyle t_Style;
	FSlateBrush t_SlateBrush;
	t_SlateBrush.SetImageSize(ButtonSize);

	t_SlateBrush.SetResourceObject(NormalStyle);
	t_Style.SetNormal(t_SlateBrush);

	t_SlateBrush.SetResourceObject(HoveredStyle);
	t_SlateBrush.TintColor = FSlateColor(HoveredColor);
	t_Style.SetHovered(t_SlateBrush);

	t_SlateBrush.SetResourceObject(PressedStyle);
	t_SlateBrush.TintColor = FSlateColor(PressedColor);
	t_Style.SetPressed(t_SlateBrush);

	WidgetStyle = t_Style;

	Super::SynchronizeProperties();
}

#if WITH_EDITOR

const FText UEasyStyleButton::GetPaletteCategory()
{
	return LOCTEXT("CyrusTools", "CyrusTools");
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE