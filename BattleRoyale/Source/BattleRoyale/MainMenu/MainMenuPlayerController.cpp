// ©Copyright DevDasTour


#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "BRGameInstance.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		ShowMainMenu();
	}
}

void AMainMenuPlayerController::ShowMainMenu()
{
	UBRGameInstance* GI = Cast<UBRGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->LoadMainMenu();
	}
}