// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 lobbyPlayerNum = GameState->PlayerArray.Num();
	
	UWorld* world = GetWorld();
	if (world) {
		if (lobbyPlayerNum == 2) {

			bUseSeamlessTravel = true;
			world->ServerTravel("/Game/Maps/PlayMap");

		}
	}
	
}
