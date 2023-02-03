// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * A Tower Shoot When See Tank In Range - Enemy
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	//When Tower Died
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	// If Anything Blocking View Of Tower
	bool CheckBlocking() const;
	// Is Tank in Range (Also Checking Tank Is ALive , Nothing Blocking View)
	bool IsInFireRange() const;
	// First Call IsInFireRange() Then If True Fire
	void FireIfInRange();
	// If Tank Is Not In Range And View, Back Tower Rotation To Default
	void CheckingTurretForRotate() const;

	// Max Fire Range Tower Can Shoot
	UPROPERTY(EditAnywhere, Category="Properties|Tower", meta=(ClampMin = 0.01f))
	float FireDistance{800};
	// Shooting Speed By Sec.
	UPROPERTY(EditAnywhere, Category="Properties|Tower", meta=(ClampMin = 0.01f))
	float FireRate{2.f};
	// Speed Of Interp Rotate To Back Default Rotation
	UPROPERTY(EditAnywhere, Category="Properties|Tower", meta=(ClampMin = 0.01f))
	float TurretBackSpeed{4};

	UPROPERTY()
	class ATank* TankPlayer;

	// Init On Game Start Rotation . Default Turret Rotation (Facing Tower When Tank Is Not In Range)
	FRotator DefaultRotation;
	FTimerHandle TimerHandle;
};
