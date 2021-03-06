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

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite)
		bool bLobbyStarted;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite)
		bool bGameStarted;

	UFUNCTION()
		void OnRep_GameOver();

	UFUNCTION(BlueprintCallable)
	void BeginPlay();

	UFUNCTION(BlueprintCallable)
	void TryStartLobbyTimer();

	FTimerHandle Handle_CountDown;

	UFUNCTION(BlueprintCallable)
		void SetLobbyTimer();

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "ServerOnline")
		int32 PlayerLeftAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerOnline")
		int32 RequiredNumToPlay = 2;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "ServerOnline")
		int32 CountDownTime = 10;

	UFUNCTION(BlueprintCallable)
		void SpawnPlane();

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "ServerOnline")
	class AActor* AirPlane;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "ServerOnline")
		class ABRSafeZone* SafeZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerOnline")
		TSubclassOf<class APlaneBase> AirPlaneClass;

	UFUNCTION(BlueprintCallable)
		void BeginGame();

	UFUNCTION(BlueprintCallable)
		void OnGameOver();
};
