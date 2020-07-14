// ©Copyright DevDasTour


#include "BRGameStateBase.h"
#include "Net/UnrealNetwork.h"

void ABRGameStateBase::OnRep_GameOver()
{
}

void ABRGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABRGameStateBase, bGameOver);
}