#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/MyScripts/Actor/Projectile.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	InitializeBaseActorComponents();
}

void ABasePawn::InitializeBaseActorComponents()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collider");
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(CapsuleComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

FRotator ABasePawn::GetTurretRotation() const
{
	return TurretMesh->GetComponentRotation();
}

FVector ABasePawn::GetTurretLocation() const
{
	return TurretMesh->GetComponentLocation();
}

void ABasePawn::TurretLookAt(const FVector TargetLocation) const
{
	//Get location Between 'Turret' and 'Target'
	const FVector LookTarget = TargetLocation - TurretMesh->GetOwner()->GetActorLocation();
	const FRotator TargetRotation = LookTarget.Rotation();

	//const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetOwner()->GetActorLocation(),TargetLocation);

	FRotator CurrentRotation = TurretMesh->GetComponentRotation();
	// Interp From Current Rotation To Target Rotation
	CurrentRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(),
	                                   TurretRotateSpeed);

	//Set Turret Yaw Rotation
	TurretMesh->SetWorldRotation(FRotator(0, CurrentRotation.Yaw, 0));
}

void ABasePawn::SetTurretRotation(const FRotator Rotation, const bool bWithInterpolation, const float Speed) const
{
	if (bWithInterpolation)
	{
		FRotator CurrentRotation = TurretMesh->GetComponentRotation();
		// Interp From Current Rotation To Target Rotation
		CurrentRotation = FMath::RInterpTo(CurrentRotation, Rotation, GetWorld()->GetDeltaSeconds(),
		                                   Speed);
		//Set Turret Yaw Rotation
		TurretMesh->SetWorldRotation(FRotator(0, CurrentRotation.Yaw, 0));
	}
	else
	{
		TurretMesh->SetWorldRotation(Rotation);
	}
}

void ABasePawn::Fire()
{
	// Spawn Projectile At SpawnPointComponent Location
	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint, ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation());
	if (!SpawnedProjectile)
	{
		// UE_LOG(LogTemp, Error, TEXT("... '%s' object"),*GetOwner()->GetActorLabel());
		return;
	}
	//Giving Spawned Projectile Owner For Damage Calculation And Self Ignore
	SpawnedProjectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	//Spawn Death Particle At Location
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	// Camera? Shake It Baby!.
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathShakeCamera); //Shake Camera
}
