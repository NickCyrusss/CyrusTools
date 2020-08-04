// Fill out your copyright notice in the Description page of Project Settings.

#include "FilterDoubleClickButton.h"

void UFilterDoubleClickButton::Tick(float DeltaTime)
{
	if (IsInCooldown())
	{
		CooldownTime -= DeltaTime;
	}
}

FReply UFilterDoubleClickButton::SlateHandleClicked()
{
	if (!IsInCooldown())
	{
		OnClicked.Broadcast();
		CooldownTime = IntervalTime;
	}
	return FReply::Handled();
}
