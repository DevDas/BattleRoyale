// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "PickupHealth.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API APickupHealth : public APickup
{
	GENERATED_BODY()

public:
	
	virtual void PickupEntered(class ABattleRoyaleCharacter* Character);

	virtual void PickupLeft(class ABattleRoyaleCharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthToGive = 50.f;
};
