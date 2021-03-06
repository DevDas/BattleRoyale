// ©Copyright DevDasTour


#include "PickupGun.h"
#include "BattleRoyaleCharacter.h"
#include "GunBase.h"
#include "Net/UnrealNetwork.h"

void APickupGun::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		if (!bDropByPlayer)
		{
			auto ClassDefault = WeaponToGive.GetDefaultObject();
			CurrentAmmoInClip = ClassDefault->CurrentAmmo;
			CurrentSpareAmmo = ClassDefault->CurrentBagAmmo; // Discuss Later
		}
	}
}

void APickupGun::PickupEntered(ABattleRoyaleCharacter* Character)
{
	Character->CurrentGunPickup = this;

}

void APickupGun::PickupLeft(ABattleRoyaleCharacter* Character)
{
	if (Character->CurrentGunPickup == this)
	{
		Character->CurrentGunPickup = nullptr;
	}
}

void APickupGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickupGun, CurrentAmmoInClip);
	DOREPLIFETIME(APickupGun, CurrentSpareAmmo);
}