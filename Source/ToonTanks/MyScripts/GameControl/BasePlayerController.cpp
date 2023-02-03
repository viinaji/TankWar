// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

void ABasePlayerController::SetPlayerControllerState(bool bEnableControl)
{
	if (bEnableControl)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bEnableControl;
}
