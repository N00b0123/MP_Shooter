// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;

UCLASS()
class MP_SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRigth(float value);
	void MoveUpDown(float value);
	void Turn(float value);
	void LookUp(float value);

private:	

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* viewCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

};
