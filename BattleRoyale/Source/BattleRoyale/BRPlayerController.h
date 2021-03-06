// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BRPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API ABRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		void BeginSpectating(class ABattleRoyaleCharacter* Killer);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerBeginSpectating(class ABattleRoyaleCharacter* Killer);

	UPROPERTY(Replicated, BlueprintReadWrite)
	class ABattleRoyaleCharacter* KilledBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABRSpectatorPawn> SpecPawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostMatchScreen")
	TSubclassOf<class UUserWidget> PostMatchScreenClass;

	UFUNCTION()
	void AddSpecScreen();

	UFUNCTION(BlueprintCallable)
	void AddPostMatchScreen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> SpecScreenClass;

	UPROPERTY(EditAnywhere, ReplicatedUsing=OnRep_IsOnPlane, BlueprintReadWrite)
		bool bIsOnPlane;

	UFUNCTION()
		void OnRep_IsOnPlane();

	UFUNCTION(BlueprintCallable)
	void OnGameBegun();

	UFUNCTION(BlueprintImplementableEvent)
	void GameBegunEvent();

	UFUNCTION(BlueprintCallable)
		void ForcePlayerToDrop();

	UFUNCTION(BlueprintCallable)
		void DropFromPlane();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerDropFromPlane();
};
