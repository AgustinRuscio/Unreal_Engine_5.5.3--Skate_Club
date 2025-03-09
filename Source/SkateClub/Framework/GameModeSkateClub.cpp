//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "GameModeSkateClub.h"
#include "SkateClubController.h"
#include "SkateClub/Widgets/GameplayWidget.h"
#include "SkateClubPlayerState.h"

namespace
{
	float TimeLeft;
}

//--------------------------------------------------------------------------------------------
AGameModeSkateClub::AGameModeSkateClub() : bGameLoop(false), GameTotalTime(30.f), GameTimer(0.f)
{
    PrimaryActorTick.bCanEverTick = true;
}

//--------------------------------------------------------------------------------------------
void AGameModeSkateClub::SetTime(float timer)
{
    GameTotalTime = timer;
    TimeLeft = GameTotalTime;
}

//--------------------------------------------------------------------------------------------
void AGameModeSkateClub::StartGame()
{
    bGameLoop = true;
    Controller->EnableInput(Controller);
}

//--------------------------------------------------------------------------------------------
void AGameModeSkateClub::BeginPlay()
{
    Super::BeginPlay();

    FTimerDelegate del;
    del.BindLambda([this] 
        {
	        Controller = Cast<ASkateClubController>(GetWorld()->GetFirstPlayerController());
            Controller->DisableInput(Controller);

	        auto widget = Controller->PushToGameplayWidgetWithReturn(LevelWidgetClass);
	        LevelWidget = Cast<UGameplayWidget>(widget);

            UpdateScore(0.f);

            ASkateClubPlayerState* PS = Controller->GetPawn()->GetPlayerState<ASkateClubPlayerState>();
            if (PS)
            {
                PS->OnScore.AddDynamic(this, &AGameModeSkateClub::UpdateScore);
            }

        });

    GetWorld()->GetTimerManager().SetTimer(Wait,del,0.2f,false);
}

//--------------------------------------------------------------------------------------------
void AGameModeSkateClub::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if(!bGameLoop) return;

    TimeLeft = GameTotalTime - GameTimer;
    GameTimer += DeltaSeconds;
    
    if (TimeLeft <= 0)
    {
        GameEnded();
        return;
    }

    if (LevelWidget)
    {
        int32 Minutes = FMath::FloorToInt(TimeLeft / 60);
        int32 Seconds = FMath::FloorToInt(FMath::Fmod(TimeLeft, 60));

        FString TimerString = FString::Printf(TEXT("%d : %d"), Minutes, Seconds);
        FText TimerText = FText::FromString(TimerString);

        LevelWidget->UpdateTimer(TimerText);
    }
}

//--------------------------------------------------------------------------------------------
void AGameModeSkateClub::UpdateScore(float NewScore)
{
    FString TimerString = FString::Printf(TEXT("%.2f"), NewScore);
    FText TimerText = FText::FromString(TimerString);

    LevelWidget->UpdateScore(TimerText);
}

//--------------------------------------------------------------------------------------------
void AGameModeSkateClub::GameEnded()
{
    OnEndGame.Broadcast();
    bGameLoop = false;
    Controller->GameEnded();
    UE_LOG(LogTemp, Warning, TEXT("End"));
}