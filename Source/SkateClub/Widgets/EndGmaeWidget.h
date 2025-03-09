//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "SkateClubBaseWidget.h"
#include "EndGmaeWidget.generated.h"

UCLASS()
class SKATECLUB_API UEndGmaeWidget : public USkateClubBaseWidget
{
	GENERATED_BODY()
	
public:	
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//
	UPROPERTY(BlueprintReadWrite, Category = Components)
	class UTextBlock* TXT_TotalScore;

	UPROPERTY(BlueprintReadOnly, Category = Components)
	FName LevelName;

	UPROPERTY(BlueprintReadWrite, Category = Components)
	FName MainMenuName = "MainMenu";
	
	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//
	UFUNCTION(BlueprintCallable)
	void RetryLevel();

	UFUNCTION(BlueprintCallable)
	void BackToMenu();

	void SetLevelName(FName CurrentLevelName);
	
	void SetTotalScore(float TotalScore);

};