// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "MenuInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "BRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API UBRGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:

	UBRGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchMaking")
		bool bUseLan;

	UFUNCTION(Exec)
	void TryJoinOrCreateGame() override;

	UFUNCTION(BlueprintCallable)
		void LoadMainMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchMaking")
		int32 NumberOfPlayers = 20;

private:

	TSubclassOf<class UUserWidget> MainMenuClass;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnFindSessionComplete(bool Success);

	class UMainMenu* MainMenu;

	void JoinSession(FOnlineSessionSearchResult SearchResult);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void CreateSession();

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);
};
