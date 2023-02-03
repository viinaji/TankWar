// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

#define OUT

void ATower::BeginPlay()
{
	Super::BeginPlay();

	TankPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	DefaultRotation = GetTurretRotation();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATower::FireIfInRange, FireRate, true);
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckingTurretForRotate();
}

void ATower::CheckingTurretForRotate() const
{
	if (IsInFireRange())
	{
		TurretLookAt(TankPlayer->GetActorLocation());
	}
	else
	{
		SetTurretRotation(DefaultRotation, true, TurretBackSpeed);
	}
}

bool ATower::CheckBlocking() const
{
	FVector StartLocation = GetTurretLocation();
	FVector EndLocation = TankPlayer->GetActorLocation();

	//Add StartLocation Higher Of Ground
	StartLocation.Z += 97.f;

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1, 0, 10);

	FHitResult Hit;
	FCollisionQueryParams QueryParams = FCollisionQueryParams(FName(TEXT("")), false, this);

	bool bHitting = GetWorld()->LineTraceSingleByObjectType(OUT Hit, StartLocation, EndLocation,
	                                                        FCollisionObjectQueryParams(ECC_OverlapAll_Deprecated),
	                                                        QueryParams);
	//Check If LineTrace Hit Is Tank Or Nothing
	if (!bHitting || Hit.GetActor() == TankPlayer)
	{
		return false;
	}
	return true;
}

bool ATower::IsInFireRange() const
{
	return FVector::Dist(GetActorLocation(), TankPlayer->GetActorLocation()) < FireDistance && !CheckBlocking() &&
		TankPlayer->IsAlive;
}

void ATower::FireIfInRange()
{
	if (IsInFireRange())
	{
		Fire();
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
