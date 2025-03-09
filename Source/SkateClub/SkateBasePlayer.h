//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "SkateBasePlayer.generated.h"

UCLASS()
class SKATECLUB_API ASkateBasePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ASkateBasePlayer();
	//----------------------------------------------//
	//				PUBLIC COMPONENTS				//
	//----------------------------------------------//

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SkateMesh;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* WidgetCompLeft;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* WidgetCompRight;

	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//

	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//
	void ObstacleJumped(float Amount);

protected:
	//----------------------------------------------//
	//				PROTECTED VARIABLE				//
	//----------------------------------------------//

	//----------------------------------------------//
	//				PROTECTED METHODS				//
	//----------------------------------------------//
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds) override;

private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float SpeedUpSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float AirControl;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float NormalFOV;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float SprintFOV;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float NormalJumpVelocity;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float SprintJumpVelocity;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FName SocketName;

	UPROPERTY(EditDefaultsOnly, Category = FeedBack)
	class UAnimMontage* JumpMontage;

	UPROPERTY(EditDefaultsOnly, Category = FeedBack)
	USoundBase* SFX_ObtainScore;
	UPROPERTY(EditDefaultsOnly, Category = FeedBack)
	USoundBase* SFX_Trick;

	class ASkateClubController* Controller;

	UPROPERTY(EditDefaultsOnly, Category = UMG)
	TSubclassOf<class UPlayerCheersWidget> PlayerCheerWidgetClass;

	class UPlayerCheersWidget* CheerWidgetLeft;
	class UPlayerCheersWidget* CheerWidgetRight;

	UPROPERTY(EditDefaultsOnly, Category = Visuals)
	UCurveFloat* CameraFOVTimeLine;
	FTimeline SprintCameraTimeLine;

	//----------------------------------------------//
	//				PRIVATE METHODS					//
	//----------------------------------------------//
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void Move(FVector2D VectorInput);

	UFUNCTION()
	void Look(FVector2D VectorInput);

	UFUNCTION()
	void Sprint(bool IsSpringting);
	
	UFUNCTION()
	void PlayerJump();

	UFUNCTION()
	void SlowDown();


	void SprintFeedBack(bool bIsSprinting);
	void JumpFeedBack();

	void ObtainedPointsFeedBack();

	UFUNCTION()
	void CameraFOVTick(float DeltaSecods);
	UFUNCTION()
	void CameraFOVFinished(float DeltaSecods);
};