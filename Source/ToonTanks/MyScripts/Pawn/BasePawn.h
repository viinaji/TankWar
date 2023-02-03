#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

/**
 * Base Pawn With Some Base Component Like Capsule,Turret,Projectile _ Functions Like Rotate,Shoot,Destroy
 */
UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	// Return Turret Rotation In World Space
	FRotator GetTurretRotation() const;
	// Return Turret Location In World Space
	FVector GetTurretLocation() const;
	//Spawn Projectile To Shoot
	void Fire();

protected:
	// Rotate Turret Face To Given Location
	void TurretLookAt(const FVector TargetLocation) const;
	/**
	 * Set Custom Turret Rotation In World Space
	 * @param Rotation Target Rotation
	 * @param bWithInterpolation Soft Rotating
	 * @param Speed	Interpolation(Soft Rotate) Speed
	 */
	void SetTurretRotation(FRotator Rotation, bool bWithInterpolation, float Speed) const;
	//This Method Call When An Actor(Pawn) Died
	virtual void HandleDestruction();

private:
	// Init Pawn Components On Construction
	void InitializeBaseActorComponents();
	// Capsule For Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	// Location For Projectile Spawn In Fire Function
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	// Turret Interp Rotation Speed
	UPROPERTY(EditAnywhere, Category="Properties|Base", meta=(ClampMin = 0.01f))
	float TurretRotateSpeed{9};
	//Reference To Projectile Actor
	UPROPERTY(EditAnywhere, Category="Properties|Base")
	TSubclassOf<class AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category="Properties|Base")
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category="Properties|Base")
	TSubclassOf<UCameraShakeBase> DeathShakeCamera;
};
