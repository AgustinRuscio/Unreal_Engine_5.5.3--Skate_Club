//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "SkateClubController.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "Framework/Application/SlateApplication.h"
#include "SkateClub/Widgets/WidgetStackBase.h"
#include "SkateClub/Widgets/WidgetPopUpBase.h"
#include "SkateClub/Widgets/EndGmaeWidget.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "CommonActivatableWidget.h"
#include <Kismet/GameplayStatics.h>
#include "SkateClubPlayerState.h"

#pragma region Feedback Methods
//--------------------------------------------------------------------------------------------
void ASkateClubController::PushObstaclePopUpWidget(TSubclassOf<UWidgetPopUpBase> PopUp, FText DisplayName, FText DisplayPoints)
{
	auto widget = PopUpsStack->PushWidgetToScreen(PopUp);

	if (auto CastedWidget = Cast<UWidgetPopUpBase>(widget))
	{
		CastedWidget->SetParentStack(PopUpsStack);
		CastedWidget->SetPopUp(DisplayName, DisplayPoints);
	}
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PushToGameplayWidget(TSubclassOf<class USkateClubBaseWidget> PopUp)
{
	GameplayStack->PushWidgetToScreen(PopUp);
}

//--------------------------------------------------------------------------------------------
UCommonActivatableWidget* ASkateClubController::PushToGameplayWidgetWithReturn(TSubclassOf<class USkateClubBaseWidget> PopUp)
{
	auto widget = GameplayStack->PushWidgetToScreen(PopUp);

	return widget;
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayCameraShake()
{
	ClientStartCameraShake(DefaultCameraShake);
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayCameraShake(TSubclassOf<UCameraShakeBase> CustomCameraShake)
{
	ClientStartCameraShake(CustomCameraShake);
}
#pragma endregion

//--------------------------------------------------------------------------------------------
void ASkateClubController::GameEnded()
{
	auto widget = PushToGameplayWidgetWithReturn(EndGameWidgetClass);

	EndGameWidget = Cast<UEndGmaeWidget>(widget);

	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	FName LevelName = FName(*CurrentLevelName);
	EndGameWidget->SetLevelName(LevelName);

	ASkateClubPlayerState* PS = GetPawn()->GetPlayerState<ASkateClubPlayerState>();
	EndGameWidget->SetTotalScore(PS->GetTotalScore());

	bShowMouseCursor = true;

	OnPlayerSlowDown.Broadcast();
	SetInputMode(FInputModeUIOnly());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::BeginPlay()
{
	Super::BeginPlay();

	SetInputs();

	CreateWidgets();
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::SetInputs()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	if (UEnhancedInputComponent* enhantedComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Movement
		enhantedComponent->BindAction(MovePlayerAction, ETriggerEvent::Triggered, this, &ASkateClubController::PlayerMovement);

		// Looking
		enhantedComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ASkateClubController::PlayerLookAround);

		// Sprint
		enhantedComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ASkateClubController::StartSprint);
		enhantedComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASkateClubController::StartSprint);

		// Jump
		enhantedComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASkateClubController::PlayerJump);

		// SlowDown
		enhantedComponent->BindAction(SlowDownAction, ETriggerEvent::Triggered, this, &ASkateClubController::PlayerSlowDown);
	}

	SetInputMode(FInputModeGameOnly());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::CreateWidgets()
{
	PopUpsStack = CreateWidget<UWidgetStackBase>(this, PopUpsStackClass);
	PopUpsStack->AddToViewport(0);

	GameplayStack = CreateWidget<UWidgetStackBase>(this, GameplayStackClass);
	GameplayStack->AddToViewport(1);
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayerMovement(const FInputActionValue& value)
{
	OnPlayerMove.Broadcast(value.Get<FVector2D>());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayerLookAround(const FInputActionValue& value)
{
	OnPlayerLookAround.Broadcast(value.Get<FVector2D>());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::StartSprint(const FInputActionValue& value)
{
	OnPlayerSprint.Broadcast(value.Get<bool>());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayerJump(const FInputActionValue& value)
{
	OnPlayerJump.Broadcast();
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayerSlowDown(const FInputActionValue& value)
{
	OnPlayerSlowDown.Broadcast();
}