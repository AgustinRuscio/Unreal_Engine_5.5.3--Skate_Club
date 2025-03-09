//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "WidgetPopUpBase.h"
#include "Components/TextBlock.h"


//--------------------------------------------------------------------------------------------
void UWidgetPopUpBase::SetPopUp(FText Object, FText Points)
{
	ObjectTxt->SetText(Object);
	PointsTxt->SetText(Points);

	int rand = FMath::RandRange(0, PosibleColors.Num()-1);
	FLinearColor LinearColor = FLinearColor(PosibleColors[rand]);

	ObjectTxt->SetColorAndOpacity(FSlateColor(LinearColor));
}