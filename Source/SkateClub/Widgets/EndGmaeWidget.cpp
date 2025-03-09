//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "EndGmaeWidget.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>

//--------------------------------------------------------------------------------------------
void UEndGmaeWidget::RetryLevel()
{
	UGameplayStatics::OpenLevel(this, LevelName);
}

//--------------------------------------------------------------------------------------------
void UEndGmaeWidget::BackToMenu()
{
	UGameplayStatics::OpenLevel(this, MainMenuName);
}

//--------------------------------------------------------------------------------------------
void UEndGmaeWidget::SetLevelName(FName CurrentLevelName)
{
	LevelName = CurrentLevelName;
}

//--------------------------------------------------------------------------------------------
void UEndGmaeWidget::SetTotalScore(float TotalScore)
{
	FString TimerString = FString::Printf(TEXT("%.2f"), TotalScore);
	FText TimerText = FText::FromString(TimerString);

	TXT_TotalScore->SetText(TimerText);
}