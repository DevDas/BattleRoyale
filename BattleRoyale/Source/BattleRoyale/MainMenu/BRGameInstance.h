// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API UBRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchMaking")
		bool bUseLan;
};
