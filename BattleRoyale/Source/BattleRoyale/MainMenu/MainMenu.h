// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 		
 */
UCLASS()
class BATTLEROYALE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetMenuInterface(IMenuInterface* MenuToInterface);

	void Setup();

	void TearDown(APlayerController* PlayerController);

protected:

	virtual bool Initialize() override;

	IMenuInterface* MenuInterface;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* FindMatchButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayText;

	FTimerHandle Handle_SearchTime;
	float SearchTime;
	void SetSearchTimeElapsed();

	// Delegates
	UFUNCTION()
	void FindAMatch();
};
