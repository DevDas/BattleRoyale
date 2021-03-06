// ©Copyright DevDasTour

#include "BRPlayerState.h"
#include "Net/UnrealNetwork.h"

void ABRPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABRPlayerState, Kills);
	DOREPLIFETIME(ABRPlayerState, Placing);
}