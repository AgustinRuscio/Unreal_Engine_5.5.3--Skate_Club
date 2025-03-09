//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "GameSetter.h"
#include "SkateClub/Framework/GameModeSkateClub.h"
#include <Kismet/GameplayStatics.h>

//--------------------------------------------------------------------------------------------
AGameSetter::AGameSetter()
{
	PrimaryActorTick.bCanEverTick = false;
}

//--------------------------------------------------------------------------------------------
void AGameSetter::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerDelegate del;
	del.BindLambda([this]
		{
			auto gameMode = Cast<AGameModeSkateClub>(GetWorld()->GetAuthGameMode());

			if (gameMode)
			{
				gameMode->SetTime(LevelTime);
				gameMode->OnEndGame.AddDynamic(this, &AGameSetter::OnEndGame);
			}

			UGameplayStatics::PlaySound2D(GetWorld(), LevelSFX);

			gameMode->StartGame();
		});

	GetWorld()->GetTimerManager().SetTimer(WaitTimerHandle, del, 0.3f, false);
}

//--------------------------------------------------------------------------------------------
void AGameSetter::OnEndGame()
{
	UGameplayStatics::PlaySound2D(GetWorld(), EndGameSFX);
}