//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeSkateClub.generated.h"

UCLASS()
class SKATECLUB_API AGameModeSkateClub : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGameModeSkateClub();
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//

	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//

private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	bool bGameLoop;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float GameTotalTime;
	float GameTimer;

	UPROPERTY(EditDefaultsOnly, Category = UMG)
	TSubclassOf<class UGameplayWidget> LevelWidgetClass;
	UGameplayWidget* LevelWidget;

	UPROPERTY(EditDefaultsOnly, Category = UMG)
	TSubclassOf<class UGameplayWidget> EndGameWidgetClass;

	class ASkateClubController* Controller;

	FTimerHandle Wait;

	//----------------------------------------------//
	//				PRIVATE METHODS					//
	//----------------------------------------------//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateScore(float NewScore);

	void GameEnded();
};