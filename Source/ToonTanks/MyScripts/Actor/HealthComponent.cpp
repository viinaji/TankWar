#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
	CurrentHealth = MaxHealth;
	GameMode = Cast<ATankWarGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                    AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth <= 0)return;
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0)
	{
		GameMode->ActorDied(DamagedActor);
	}
}
