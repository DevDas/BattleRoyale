// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "PickupAmmo.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API APickupAmmo : public APickup
{
	GENERATED_BODY()
	
public:

	virtual void PickupEntered(class ABattleRoyaleCharacter* Character);

	virtual void PickupLeft(class ABattleRoyaleCharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoToGive = 30;
};
