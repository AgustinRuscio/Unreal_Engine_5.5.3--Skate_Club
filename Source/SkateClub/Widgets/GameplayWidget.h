//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "SkateClubBaseWidget.h"
#include "GameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class SKATECLUB_API UGameplayWidget : public USkateClubBaseWidget
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//
	UPROPERTY(BlueprintReadWrite, Category = Components)
	class UTextBlock*  TXT_Timer;

	UPROPERTY(BlueprintReadWrite, Category = Components)
	class UTextBlock* TXT_Score;

	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//
	void UpdateScore(FText NewScore);

	void UpdateTimer(FText NewTime);
};