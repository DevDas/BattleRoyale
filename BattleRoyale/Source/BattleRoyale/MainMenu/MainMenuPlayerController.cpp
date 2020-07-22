// ©Copyright DevDasTour


#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"

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
	UUserWidget* MainMenuScreen = CreateWidget(this, MainMenuWidgetClass);
	if (!MainMenuScreen) return;
	MainMenuScreen->AddToViewport();
}