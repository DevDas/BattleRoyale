// ©Copyright DevDasTour

#include "BRPlayerController.h"
#include "BattleRoyaleCharacter.h"
#include "Net/UnrealNetwork.h"
#include "BRSpectatorPawn.h"
#include "BRGameStateBase.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ABRPlayerController::BeginSpectating(ABattleRoyaleCharacter* Killer)
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerBeginSpectating(Killer);
	}
	// TODO
	if (Killer)
	{
		KilledBy = Killer;
		if (SpecPawnClass)
		{
			ABRSpectatorPawn* SpecActor = GetWorld()->SpawnActor<ABRSpectatorPawn>(SpecPawnClass, GetPawn()->GetActorTransform());
			if (SpecActor)
			{
				SpecActor->SetOwner(this);
				SpecActor->AttachToActor(KilledBy, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				Possess(SpecActor);
				AddSpecScreen();
			}
		}
	}
	else
	{
		AddPostMatchScreen();
	}
}

void ABRPlayerController::ServerBeginSpectating_Implementation(ABattleRoyaleCharacter* Killer)
{
	BeginSpectating(Killer);
}

bool ABRPlayerController::ServerBeginSpectating_Validate(ABattleRoyaleCharacter* Killer) { return true; }

void ABRPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABRPlayerController, KilledBy); 
	DOREPLIFETIME(ABRPlayerController, bIsOnPlane);
}

void ABRPlayerController::AddSpecScreen()
{
	if (IsLocalController())
	{
		ABRGameStateBase* GS = Cast<ABRGameStateBase>(GetWorld()->GetGameState());
		if (GS && !GS->bGameOver)
		{
			UWidgetLayoutLibrary::RemoveAllWidgets(this);
			UUserWidget* SpecScreen = CreateWidget(this, SpecScreenClass, "SpecScreen");
			if (SpecScreen)
			{
				SpecScreen->AddToViewport();
			}
		}
	}
}

void ABRPlayerController::AddPostMatchScreen()
{
	if (IsLocalController())
	{
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
		UUserWidget* PostMatchScreen = CreateWidget<UUserWidget>(this, PostMatchScreenClass);
		if (!PostMatchScreen) return;
		PostMatchScreen->AddToViewport();
		bShowMouseCursor = true;

		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(PostMatchScreen->TakeWidget());
		SetInputMode(InputModeData);
	}
}

void ABRPlayerController::OnRep_IsOnPlane()
{
	GameBegunEvent();
}

void ABRPlayerController::OnGameBegun()
{
	if (IsLocalController())
	{
		 // TO Setup Widget Stuff In Blueprint
		FTimerHandle Handle_ForcePlayerToDrop;
		GetWorldTimerManager().SetTimer(Handle_ForcePlayerToDrop, this, &ABRPlayerController::ForcePlayerToDrop, 40.f, false);
	}
}

void ABRPlayerController::ForcePlayerToDrop()
{
	if (bIsOnPlane)
	{
		DropFromPlane();
	}
}

void ABRPlayerController::DropFromPlane()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerDropFromPlane();
	}

	bIsOnPlane = false;
	ABRGameStateBase* GS = Cast<ABRGameStateBase>(GetWorld()->GetGameState());
	if (GS && GS->AirPlane)
	{
		GetPawn()->SetActorTransform(GS->AirPlane->GetActorTransform());
		SetControlRotation(GS->AirPlane->GetActorRotation());
		SetViewTargetWithBlend(GetPawn(), 1.f, EViewTargetBlendFunction::VTBlend_Cubic);
		
		ABattleRoyaleCharacter* PlayerPawn = Cast<ABattleRoyaleCharacter>(GetPawn());
		if (PlayerPawn)
		{
			PlayerPawn->SetFlying(true);
		}
	}
}

void ABRPlayerController::ServerDropFromPlane_Implementation()
{
	DropFromPlane();
}

bool ABRPlayerController::ServerDropFromPlane_Validate() { return true; }