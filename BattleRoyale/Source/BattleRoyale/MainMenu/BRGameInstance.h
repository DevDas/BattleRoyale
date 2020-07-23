// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
//#include "MainMenu/MenuInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "BRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API UBRGameInstance : public UGameInstance//, public IMenuInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchMaking")
		bool bUseLan;

	UFUNCTION(BlueprintCallable)
	void TryJoinOrCreateGame();
};
