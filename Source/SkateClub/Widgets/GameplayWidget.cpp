//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "GameplayWidget.h"
#include "Components/TextBlock.h"

//--------------------------------------------------------------------------------------------
void UGameplayWidget::UpdateScore(FText NewScore)
{
	TXT_Score->SetText(NewScore);
}

//--------------------------------------------------------------------------------------------
void UGameplayWidget::UpdateTimer(FText NewTime)
{
	TXT_Timer->SetText(NewTime);
}