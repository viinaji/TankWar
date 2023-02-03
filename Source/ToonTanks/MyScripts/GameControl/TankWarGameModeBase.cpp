#include "TankWarGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ATankWarGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleStartup();
}

void ATankWarGameModeBase::HandleStartup()
{
	TankActor = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!TankActor)
	{
		// UE_LOG(LogTemp, Error, TEXT("... '%s' object"),*GetOwner()->GetActorLabel());
	}
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
	{
		// UE_LOG(LogTemp, Error, TEXT("... '%s' object"),*GetOwner()->GetActorLabel());
	}
	PlayerController->SetPlayerControllerState(false);
	CountTowers();
	StartGame();
	// StartUp Delay For Showing Widget
	FTimerHandle TimerHandle;
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(PlayerController,
	                                                                   &ABasePlayerController::SetPlayerControllerState,
	                                                                   true);
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DelayStartup, false);
}

void ATankWarGameModeBase::CountTowers()
{
	// Init Array With All Actors Of ATower Class Exist In Game World
	TArray<AActor*> TowersInWorld;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowersInWorld);
	TowerCountInWorld = TowersInWorld.Num();
}

void ATankWarGameModeBase::ActorDied(AActor* DeadActor)
{
	if (!DeadActor)
	{
		// UE_LOG(LogTemp, Error, TEXT("... '%s' object"),*GetOwner()->GetActorLabel());
		return;
	}
	if (DeadActor == TankActor)
	{
		TankActor->HandleDestruction();
		PlayerController->SetPlayerControllerState(false);
		EndGame(false);
	}
	else if (ATower* Tower = Cast<ATower>(DeadActor))
	{
		Tower->HandleDestruction();
		TowerCountInWorld--;
		if (TowerCountInWorld <= 0)
		{
			PlayerController->SetPlayerControllerState(false);
			EndGame(true);
		}
	}
}
