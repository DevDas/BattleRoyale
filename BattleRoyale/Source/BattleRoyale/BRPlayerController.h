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

	UFUNCTION()
	void AddSpecScreen();

	UFUNCTION()
	void AddPostMatchScreen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> SpecScreenClass;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite)
		bool bIsOnPlane;

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
