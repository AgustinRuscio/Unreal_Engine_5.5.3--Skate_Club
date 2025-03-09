//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "PlayerCheersWidget.h"
#include "Components/TextBlock.h"

//--------------------------------------------------------------------------------------------
bool UPlayerCheersWidget::GetIsVisible() const
{
	return (GetVisibility() == ESlateVisibility::Visible);
}

//--------------------------------------------------------------------------------------------
void UPlayerCheersWidget::ShowText()
{
	int rand = FMath::RandRange(0, PossibleWords.Num() - 1);
	FText text = PossibleWords[rand];

	Text->SetText(text);

	int rand2 = FMath::RandRange(0, PossibleColors.Num() - 1);
	FLinearColor color = PossibleColors[rand2];
	Text->SetColorAndOpacity(color);

	SetVisibility(ESlateVisibility::Visible);
	OnShow();

	if (!GetWorld()->GetTimerManager().IsTimerActive(HideTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UPlayerCheersWidget::SelfRemove, TimeOnScreen, false);
	}
}

//--------------------------------------------------------------------------------------------
void UPlayerCheersWidget::SelfRemove()
{
	OnHide();
	SetVisibility(ESlateVisibility::Hidden);

	if (GetWorld()->GetTimerManager().IsTimerActive(HideTimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(HideTimerHandle);
}