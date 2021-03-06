// ©Copyright DevDasTour

#include "BRGameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "PlaneBase.h"
#include "BattleRoyaleGameMode.h"
#include "BRPlayerController.h"
#include "BRSafeZone.h"
#include "BRPlayerState.h"

void ABRGameStateBase::BeginPlay()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		TryStartLobbyTimer();
	}
}

void ABRGameStateBase::OnRep_GameOver()
{
	if (bGameOver)
	{
		ABRPlayerController* PC = Cast<ABRPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC)
		{
			PC->AddPostMatchScreen();
		}
	}
}

void ABRGameStateBase::OnGameOver()
{
	bGameOver = true;
}

void ABRGameStateBase::TryStartLobbyTimer()
{
	if (PlayerLeftAlive >= RequiredNumToPlay)
	{
		bLobbyStarted = true;
		GetWorldTimerManager().SetTimer(Handle_CountDown, this, &ABRGameStateBase::SetLobbyTimer, 1, true);
	}
	else
	{
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, this, &ABRGameStateBase::TryStartLobbyTimer, 1, false); // Check if Enough Player To Play
	}
}

void ABRGameStateBase::SetLobbyTimer()
{
	CountDownTime--;
	if (CountDownTime == 3)
	{
		SpawnPlane();
	}
	else
	{
		if (CountDownTime <= 0)
		{
			BeginGame();
		}
	}
	
}

void ABRGameStateBase::BeginGame()
{
	// TODO Begin The Game
	GetWorldTimerManager().ClearTimer(Handle_CountDown);
	bGameStarted = true;

	ABattleRoyaleGameMode* GM = Cast<ABattleRoyaleGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->OnGameStart();
		if (SafeZone)
		{
			SafeZone->EnableSafeZone();
		}

		// Set Placing For All Player
		for (ABRPlayerController* PC : GM->AlivePlayerControllerList)
		{
			if (!PC) return;

			ABRPlayerState* PlayerState = Cast<ABRPlayerState>(PC->PlayerState);
			if (!PlayerState) return;
			PlayerState->Placing = GM->AlivePlayerControllerList.Num();
		}
	}
}

void ABRGameStateBase::SpawnPlane()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		AirPlane = GetWorld()->SpawnActor<AActor>(AirPlaneClass);
	}
}

void ABRGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABRGameStateBase, bGameOver);
	DOREPLIFETIME(ABRGameStateBase, PlayerLeftAlive);
	DOREPLIFETIME(ABRGameStateBase, bLobbyStarted);
	DOREPLIFETIME(ABRGameStateBase, CountDownTime);
	DOREPLIFETIME(ABRGameStateBase, AirPlane);
	DOREPLIFETIME(ABRGameStateBase, bGameStarted);
	DOREPLIFETIME(ABRGameStateBase, SafeZone);
}