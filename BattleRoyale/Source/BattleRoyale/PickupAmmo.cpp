// ©Copyright DevDasTour


#include "PickupAmmo.h"
#include "BattleRoyaleCharacter.h"
#include "GunBase.h"

void APickupAmmo::PickupEntered(ABattleRoyaleCharacter* Character)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (Character->Gun)
		{
			Character->Gun->GiveAmmo(AmmoToGive);
			Destroy();
		}
	}
}

void APickupAmmo::PickupLeft(ABattleRoyaleCharacter* Character)
{

}