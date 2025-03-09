//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "SkateBasePlayer.h"
#include <Camera/CameraComponent.h>
#include <Components/WidgetComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SkateClub/Framework/SkateClubController.h"
#include <Kismet/GameplayStatics.h>
#include "Framework/SkateClubPlayerState.h"
#include "SkateClub/Widgets/PlayerCheersWidget.h"
#include "Widgets/WidgetPopUpBase.h"

namespace
{
	float LastObstacleJumpedTime = 0;
}

//--------------------------------------------------------------------------------------------
ASkateBasePlayer::ASkateBasePlayer() : WalkSpeed(400.f), SpeedUpSpeed(700.f), AirControl(0.01f), NormalFOV(90.f), SprintFOV(120.f), NormalJumpVelocity(420.f), SprintJumpVelocity(550.f)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComp->SetupAttachment(GetMesh());

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);

	SkateMesh = CreateDefaultSubobject<UStaticMeshComponent>("Skate Mesh");
	SkateMesh->SetupAttachment(GetMesh());

	WidgetCompLeft = CreateDefaultSubobject<UWidgetComponent>("Cheers Widget Left");
	WidgetCompLeft->SetupAttachment(GetMesh());
	WidgetCompLeft->SetWidgetClass(PlayerCheerWidgetClass);

	WidgetCompRight = CreateDefaultSubobject<UWidgetComponent>("Cheers WidgetRight");
	WidgetCompRight->SetupAttachment(GetMesh());
	WidgetCompRight->SetWidgetClass(PlayerCheerWidgetClass);

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->MaxWalkSpeed				  = WalkSpeed;
	GetCharacterMovement()->JumpZVelocity				  = NormalJumpVelocity;
	GetCharacterMovement()->AirControl					  = AirControl;
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::ObstacleJumped(float Amount, TSubclassOf<UWidgetPopUpBase> PopUp, FText DisplayName, FText DisplayPoints)
{
	if(!GetCharacterMovement()->IsFalling()) return;

	Controller->PushObstaclePopUpWidget(PopUp, DisplayName, DisplayPoints);
	Controller->PlayCameraShake();

	ASkateClubPlayerState* PS = GetPlayerState<ASkateClubPlayerState>();

	if (PS)
		PS->AddScore(Amount);

	ObtainedPointsFeedBack();
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::BeginPlay()
{
	Super::BeginPlay();

	CheerWidgetLeft = Cast<UPlayerCheersWidget>(WidgetCompLeft->GetUserWidgetObject());
	CheerWidgetRight = Cast<UPlayerCheersWidget>(WidgetCompRight->GetUserWidgetObject());
	CheerWidgetLeft->SetVisibility(ESlateVisibility::Hidden);
	CheerWidgetRight->SetVisibility(ESlateVisibility::Hidden);

	//--- FOV
	FOnTimelineFloat CamFOVTick;
	CamFOVTick.BindUFunction(this, FName("CameraFOVTick"));
	SprintCameraTimeLine.AddInterpFloat(CameraFOVTimeLine, CamFOVTick);

	FOnTimelineEventStatic CameraFOVFinished;
	CameraFOVFinished.BindUFunction(this, FName("CameraFOVFinished"));
	SprintCameraTimeLine.SetTimelineFinishedFunc(CameraFOVFinished);
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SprintCameraTimeLine.TickTimeline(DeltaSeconds);
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	Controller = Cast<ASkateClubController>(GetWorld()->GetFirstPlayerController());

	if (!Controller) return;

	Controller->OnPlayerMove.AddDynamic(this, &ASkateBasePlayer::Move);
	Controller->OnPlayerLookAround.AddDynamic(this, &ASkateBasePlayer::Look);
	Controller->OnPlayerSprint.AddDynamic(this, &ASkateBasePlayer::Sprint);
	Controller->OnPlayerJump.AddDynamic(this, &ASkateBasePlayer::PlayerJump);
	Controller->OnPlayerSlowDown.AddDynamic(this, &ASkateBasePlayer::SlowDown);
}

#pragma region Input Actions Methods
//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::Move(FVector2D VectorInput)
{
	const FRotator moveRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	const FVector directionVector = moveRotation.RotateVector(FVector::ForwardVector);
	AddMovementInput(directionVector, VectorInput.Y);
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::Look(FVector2D VectorInput)
{
	AddControllerYawInput(VectorInput.X);
	AddControllerPitchInput(VectorInput.Y);
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::Sprint(bool IsSpringting)
{
if( GetCharacterMovement()->Velocity.Length() <= 0) return;

	GetCharacterMovement()->MaxWalkSpeed = IsSpringting ? SpeedUpSpeed : WalkSpeed;
	GetCharacterMovement()->JumpZVelocity = IsSpringting ? SprintJumpVelocity : NormalJumpVelocity;
	SprintFeedBack(IsSpringting);
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::PlayerJump()
{
	if(GetCharacterMovement()->IsFalling()) return;

	Jump();
	JumpFeedBack();
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::SlowDown()
{
	if (GetCharacterMovement()->IsFalling()) return;

	GetCharacterMovement()->StopMovementImmediately();
}
#pragma endregion

#pragma region Feedback Methods
//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::SprintFeedBack(bool bIsSprinting)
{
	if (bIsSprinting)
		SprintCameraTimeLine.Play();
	else
		SprintCameraTimeLine.Reverse();
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::JumpFeedBack()
{
	UAnimInstance* AnimIstance = GetMesh()->GetAnimInstance();

	if (AnimIstance)
		AnimIstance->Montage_Play(JumpMontage);
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::ObtainedPointsFeedBack()
{
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_ObtainScore);
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_Trick);
	
	if (CheerWidgetRight->GetIsVisible())
	{
		if(!CheerWidgetLeft->GetIsVisible())
			CheerWidgetLeft->ShowText();
	}
	else
	{
		CheerWidgetRight->ShowText();
	}
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::CameraFOVTick(float DeltaSecods)
{
	float lerpedFOV = FMath::Lerp(NormalFOV, SprintFOV, DeltaSecods);

	CameraComp->SetFieldOfView(lerpedFOV);
}

//--------------------------------------------------------------------------------------------
void ASkateBasePlayer::CameraFOVFinished(float DeltaSecods) { }
#pragma endregion