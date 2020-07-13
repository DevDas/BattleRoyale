// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "PickupGun.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API APickupGun : public APickup
{
	GENERATED_BODY()	

public:
	
	virtual void PickupEntered(class ABattleRoyaleCharacter* Character);

	virtual void PickupLeft(class ABattleRoyaleCharacter* Character);
};
