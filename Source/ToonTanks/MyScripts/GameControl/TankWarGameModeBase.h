// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanks/MyScripts/Pawn/Tank.h"
#include "ToonTanks/MyScripts/Pawn/Tower.h"
#include "ToonTanks/MyScripts/GameControl/BasePlayerController.h"
#include "TankWarGameModeBase.generated.h"

/**
 * This Class Handle Starting Game,Ending Game,Number Of Towers Alive
 */
UCLASS()
class TOONTANKS_API ATankWarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// When Tank or Tower Destroyed
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	// Functions To Be Called In Blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void EndGame(bool bWon);

private:
	void HandleStartup();
	// Counting Tower Enemies In World For Lose Of Win
	void CountTowers();

	// Delay Before Game Start
	UPROPERTY(EditAnywhere)
	float DelayStartup{4.7f};

	UPROPERTY()
	ATank* TankActor;
	UPROPERTY()
	ATower* TowerActor;
	UPROPERTY()
	ABasePlayerController* PlayerController;
	// How Many Tower Exist In Game World
	int32 TowerCountInWorld;
};
