//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "SkateClubBaseWidget.h"
#include "WidgetPopUpBase.generated.h"


UCLASS()
class SKATECLUB_API UWidgetPopUpBase : public USkateClubBaseWidget
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//
	UPROPERTY(BlueprintReadWrite, Category = Components)
	class UTextBlock*  ObjectTxt;

	UPROPERTY(BlueprintReadWrite, Category = Components)
	class UTextBlock* PointsTxt;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TArray<FColor> PosibleColors;


	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//
	void SetPopUp(FText Object, FText Points);
};