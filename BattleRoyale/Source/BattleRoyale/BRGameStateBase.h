// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BRGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API ABRGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere,ReplicatedUsing=OnRep_GameOver, BlueprintReadWrite)
		bool bGameOver;

	UFUNCTION()
		void OnRep_GameOver();
};
