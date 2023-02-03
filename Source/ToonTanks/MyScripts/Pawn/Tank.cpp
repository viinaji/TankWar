// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
	InitializeActorComponents();
}

void ATank::InitializeActorComponents()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController)
	{
		/*UE_LOG(LogTemp, Error, TEXT("Cant initialize 'APlayerController' on '%s' object"),
		       *GetOwner()->GetActorLabel());*/
	}
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TurretLookAt(GetMouseLocationInWorld());
}

FVector ATank::GetMouseLocationInWorld() const
{
	FHitResult HitUnderMouse;
	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitUnderMouse);
	if (!HitUnderMouse.IsValidBlockingHit())
	{
		// UE_LOG(LogTemp, Warning, TEXT("... '%s' object"),*GetOwner()->GetActorLabel());
		return FVector::Zero();
	}
	return HitUnderMouse.ImpactPoint;
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePawn::Fire);
}

void ATank::Move(const float Value)
{
	InitMovingStatus(Value);

	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float Speed = (Value * MoveSpeed * DeltaTime) * 10;

	CurrentMove = FMath::FInterpTo(CurrentMove, Speed, DeltaTime, MoveInterpolationSpeed / 10);

	AddActorLocalOffset(FVector(CurrentMove, 0, 0), true);
}

void ATank::InitMovingStatus(const float Value)
{
	//Tank Not Moving
	if (Value == 0)
	{
		IsMoving = false;
		return;;
	}

	//Tank Moving
	IsMoving = true;

	//Moving Forward
	if (Value > 0)
	{
		IsMovingForward = true;
		return;
	}

	//Moving Backward
	IsMovingForward = false;
}

void ATank::Turn(float Value)
{
	//If Moving Backward Switch Left and Right
	if (IsMoving && !IsMovingForward)
	{
		Value *= -1; //Toggle To Positive Or Negative
	}

	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float Speed = Value * TurnSpeed * DeltaTime;

	CurrentRotate = FMath::FInterpTo(CurrentRotate, Speed, DeltaTime, RotateInterpolationSpeed / 10);

	AddActorLocalRotation(FRotator(0, CurrentRotate, 0));
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	IsAlive = false;
}
