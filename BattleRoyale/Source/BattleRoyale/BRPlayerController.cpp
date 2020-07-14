// ©Copyright DevDasTour

#include "BRPlayerController.h"
#include "BattleRoyaleCharacter.h"
#include "Net/UnrealNetwork.h"
#include "BRSpectatorPawn.h"
#include "BRGameStateBase.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

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
		ABRGameStateBase* GS = Cast<ABRGameStateBase>(GetWorld()->GetGameState());
		if (GS)
		{

		}
	}
}
