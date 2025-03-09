//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include <EnhancedInputLibrary.h>
#include "GameFramework/PlayerController.h"
#include "SkateClubController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerMovement, FVector2D, VectorInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerLookAround, FVector2D, VectorInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSprint, bool, bIsSprinting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJump);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlowDown);

UCLASS()
class SKATECLUB_API ASkateClubController : public APlayerController
{
	GENERATED_BODY()
public:
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//

	FPlayerMovement OnPlayerMove;
	FPlayerLookAround OnPlayerLookAround;
	FSprint OnPlayerSprint;
	FJump OnPlayerJump;
	FSlowDown OnPlayerSlowDown;

	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//

	void PushObstaclePopUpWidget(TSubclassOf<class UWidgetPopUpBase> PopUp, FText DisplayName, FText DisplayPoints);

	void PushToGameplayWidget(TSubclassOf<class USkateClubBaseWidget> PopUp);
	class UCommonActivatableWidget* PushToGameplayWidgetWithReturn(TSubclassOf<class USkateClubBaseWidget> PopUp);

	void PlayCameraShake();
	void PlayCameraShake(TSubclassOf<UCameraShakeBase> CustomCameraShake);

private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MovePlayerAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* LookAroundAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SlowDownAction;


	UPROPERTY(EditDefaultsOnly, Category = UMG)
	TSubclassOf<class UWidgetStackBase> PopUpsStackClass;
	class UWidgetStackBase* PopUpsStack;

	UPROPERTY(EditDefaultsOnly, Category = UMG)
	TSubclassOf<class UWidgetStackBase> GameplayStackClass;
	class UWidgetStackBase* GameplayStack;


	UPROPERTY(EditDefaultsOnly, Category = FeedBack)
	TSubclassOf<UCameraShakeBase> DefaultCameraShake;

	//----------------------------------------------//
	//				PRIVATE METHODS					//
	//----------------------------------------------//
	virtual void BeginPlay() override;

	void SetInputs();
	void CreateWidgets();

	void PlayerMovement(const FInputActionValue& value);
	void PlayerLookAround(const FInputActionValue& value);
	void StartSprint(const FInputActionValue& value);
	void PlayerJump(const FInputActionValue& value);
	void PlayerSlowDown(const FInputActionValue& value);
};