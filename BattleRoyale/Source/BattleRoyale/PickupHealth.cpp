// ©Copyright DevDasTour


#include "PickupHealth.h"
#include "BattleRoyaleCharacter.h"

void APickupHealth::PickupEntered(ABattleRoyaleCharacter* Character)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (Character->Health < Character->MaxHealth)
		{
			Character->ModifyHealth(HealthToGive * -1);
			Destroy();
		}
	}
}

void APickupHealth::PickupLeft(ABattleRoyaleCharacter* Character)
{

}