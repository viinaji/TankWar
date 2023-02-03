#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	                       FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

private:
	//Init Components Like Movement,TrailParticle,Mesh on Construction
	void InitializeActorComponents();

	// Power Of Projectile Damage
	UPROPERTY(EditAnywhere)
	float Damage{50};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* HitParticle;
	UPROPERTY(VisibleAnywhere, Category="Effects")
	UParticleSystemComponent* TrailEffect;
	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UCameraShakeBase> HitCameraShake;
};
