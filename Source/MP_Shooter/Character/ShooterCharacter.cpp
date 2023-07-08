// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "MP_Shooter/Weapon/Weapon.h"


AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(GetMesh());
	springArm->TargetArmLength = 300.f;
	springArm->bUsePawnControlRotation = true;

	viewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	viewCamera->SetupAttachment(springArm, USpringArmComponent::SocketName);
	viewCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);

}

void AShooterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AShooterCharacter, OverlappingWeapon, COND_OwnerOnly);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, & ACharacter::Jump);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ThisClass::MoveRigth);
	PlayerInputComponent->BindAxis(FName("MoveUpDown"), this, &ThisClass::MoveUpDown);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ThisClass::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ThisClass::LookUp);

}

void AShooterCharacter::SetOverlappingWeapon(AWeapon* Weapon)
{

	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false);
	}
	OverlappingWeapon = Weapon;
	if (IsLocallyControlled())
	{
		if (OverlappingWeapon)
		{
			OverlappingWeapon->ShowPickupWidget(true);
		}
	}
}

void AShooterCharacter::OnRep_OverlappingWeapon(AWeapon* LastWeapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}
	if (LastWeapon)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}

void AShooterCharacter::MoveForward(float value)
{
	if (Controller && value != 0.f)
	{
		const FRotator controlRotation = GetControlRotation();
		const FRotator yawnRotation(0.f, controlRotation.Yaw, 0.f);
		const FVector direction = FRotationMatrix(yawnRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void AShooterCharacter::MoveRigth(float value)
{
	if (Controller && value != 0.f)
	{
		const FRotator controlRotation = GetControlRotation();
		const FRotator yawnRotation(0.f, controlRotation.Yaw, 0.f);
		const FVector direction = FRotationMatrix(yawnRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}

void AShooterCharacter::MoveUpDown(float value)
{
	AddControllerPitchInput(value);
}


void AShooterCharacter::Turn(float value)
{
	AddControllerYawInput(value);
}


void AShooterCharacter::LookUp(float value)
{
	AddControllerPitchInput(value);
}
