#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToonTanks/MyScripts/GameControl/TankWarGameModeBase.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	                  AActor* DamageCauser);
private:
	UPROPERTY(EditAnywhere, Category="Values")
	float MaxHealth{100.f};

	UPROPERTY()
	ATankWarGameModeBase* GameMode;

	float CurrentHealth;
};
