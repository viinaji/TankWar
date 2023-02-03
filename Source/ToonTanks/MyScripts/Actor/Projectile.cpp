#include "Projectile.h"

#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	InitializeActorComponents();
}

void AProjectile::InitializeActorComponents()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>("Trail Particle");
	TrailEffect->SetupAttachment(RootComponent);
}


void AProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
                            FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (GetOwner() == nullptr)
	{
		Destroy();
		return;
	}
	if (Other && Other != GetOwner() && Other != this)
	{
		UGameplayStatics::ApplyDamage(Other, Damage, GetOwner()->GetInstigatorController(), this,
		                              UDamageType::StaticClass());

		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());

		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);

		Destroy();
	}
}
