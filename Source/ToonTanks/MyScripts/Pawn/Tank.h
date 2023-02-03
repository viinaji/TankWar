// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * A Tank That Player Control To Move And Fire At Towers And Destroy Them
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	// When Player Died
	virtual void HandleDestruction() override;
	// Omg! What is this Variable?
	bool IsAlive{true};

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	// Init Components Like SpringArm And Camera
	void InitializeActorComponents();
	// Status Off Tank Locomotion, Like:IsMoving?
	void InitMovingStatus(const float Value);
	// Get Impact Location Of Cursor Pointing
	FVector GetMouseLocationInWorld() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY()
	APlayerController* PlayerController;

	// Tank Moving Speed
	UPROPERTY(EditAnywhere, Category="Properties|Tank",meta=(ClampMin = 0.01f))
	float MoveSpeed{100.f};
	// Smooth Move Speed
	UPROPERTY(EditAnywhere, Category="Properties|Tank",meta=(ClampMin = 0.01f))
	float MoveInterpolationSpeed{40.f};
	// Turret Rotation Speed
	UPROPERTY(EditAnywhere, Category="Properties|Tank",meta=(ClampMin = 0.01f))
	float TurnSpeed{150.f};
	// Turret Smooth Rotate Speed
	UPROPERTY(EditAnywhere, Category="Properties|Tank",meta=(ClampMin = 0.01f))
	float RotateInterpolationSpeed{30.f};

	// Move The Tank in Directions
	void Move(float Value);
	//Rotate Turret Base On Cursor Location
	void Turn(float Value);

	//For Interpolation Purposes
	float CurrentMove{0};
	//For Interpolation Purposes
	float CurrentRotate{0};

	// Moving In Any Direction?
	bool IsMoving;
	bool IsMovingForward;
};
