// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BRPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API ABRPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "PlayerScore")
		int32 Kills;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "PlayerScore")
		int32 Placing;
};