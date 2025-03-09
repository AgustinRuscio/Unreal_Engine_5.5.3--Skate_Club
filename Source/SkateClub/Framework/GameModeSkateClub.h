//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeSkateClub.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndGame);

UCLASS()
class SKATECLUB_API AGameModeSkateClub : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGameModeSkateClub();
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//
	FOnEndGame OnEndGame;

	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//
	void SetTime(float timer);
	void StartGame();
private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	bool bGameLoop;
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