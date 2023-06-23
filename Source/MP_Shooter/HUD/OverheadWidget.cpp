// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;

	switch (LocalRole)
	{
	case ENetRole::ROLE_None:
		Role = FString("ROLE_None");
		break;

	case ENetRole::ROLE_SimulatedProxy: 
		Role = FString("ROLE_SimulatedProxy");
		break;

	case ENetRole::ROLE_AutonomousProxy: 
		Role = FString("ROLE_AutonomousProxy");
		break;

	case ENetRole::ROLE_Authority:
		Role = FString("ROLE_Authority");
		break;

	case ENetRole::ROLE_MAX: 
		Role = FString("ROLE_MAX");
		break;

	default:
		break;
	}
	FString LocalRoleString = FString::Printf(TEXT("Local Role: %s"), *Role);

	SetDisplayText(LocalRoleString);

}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();

	Super::NativeDestruct();
}
