// Fill out your copyright notice in the Description page of Project Settings.


#include "EdgeScrollComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UEdgeScrollComponent::UEdgeScrollComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEdgeScrollComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEdgeScrollComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckEdgeScroll();
}

void UEdgeScrollComponent::CheckEdgeScroll()
{
	FVector2D t_MousePos;
	FVector2D t_ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	APlayerController* t_Controller = Cast<APlayerController>(GetOwner());
	if (!t_Controller)
		return;

	APawn* t_Pawn = t_Controller->GetPawn();
	if (t_Pawn && t_Controller->GetMousePosition(t_MousePos.X, t_MousePos.Y))
	{
		if (t_MousePos.X / t_ViewportSize.X < 0.01)//�����
		{
			t_Pawn->AddMovementInput(FRotationMatrix(t_Controller->GetControlRotation()).GetScaledAxis(EAxis::Y), -1 * EdgeScrollSpeed);
		}
		if (t_MousePos.X / t_ViewportSize.X > 0.99)//�ҹ���
		{
			t_Pawn->AddMovementInput(FRotationMatrix(t_Controller->GetControlRotation()).GetScaledAxis(EAxis::Y), 1 * EdgeScrollSpeed);
		}
		if (t_MousePos.Y / t_ViewportSize.Y < 0.01)//�Ϲ���
		{
			t_Pawn->AddMovementInput(t_Controller->GetControlRotation().Vector(), 1 * EdgeScrollSpeed);
		}
		if (t_MousePos.Y / t_ViewportSize.Y > 0.99)//�¹���
		{
			t_Pawn->AddMovementInput(t_Controller->GetControlRotation().Vector(), -1 * EdgeScrollSpeed);
		}
	}
	else //����������ϽǱ�Եʱ,GetMousePosition��Ч
	{
		t_MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		if (t_MousePos.X / t_ViewportSize.X < 0.01)//�����
		{
			t_Pawn->AddMovementInput(FRotationMatrix(t_Controller->GetControlRotation()).GetScaledAxis(EAxis::Y), -1 * EdgeScrollSpeed);
		}
		if (t_MousePos.Y / t_ViewportSize.Y < 0.01)//�Ϲ���
		{
			t_Pawn->AddMovementInput(t_Controller->GetControlRotation().Vector(), 1 * EdgeScrollSpeed);
		}
	}
}

