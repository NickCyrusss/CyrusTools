// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUMG/EasyStyleButton.h"
#include "Tickable.h"
#include "FilterDoubleClickButton.generated.h"

/**
 * 防止误触或者触摸导致的极短时间内点击按钮两次的情况
 */
UCLASS()
class CYRUSTOOLS_API UFilterDoubleClickButton : public UEasyStyleButton , public FTickableGameObject
{
	GENERATED_BODY()
public:

	/** 两次点击间允许的间隔时间(冷却时间) */
	UPROPERTY(EditAnywhere, Category = "Data")
		float IntervalTime = 0.3f;

public:

	/** FTickableEditorObject Interface */
	virtual void Tick(float DeltaTime);
	virtual TStatId GetStatId() const 
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UFilterDoubleClickButton, STATGROUP_Tickables);
	};

	bool IsInCooldown() { return CooldownTime > 0; }

protected:
	virtual FReply SlateHandleClicked();
	
private:
	float CooldownTime = 0;
};
