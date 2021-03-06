// ©Copyright DevDasTour

#include "MainMenu.h"
#include "Components/Button.h"
#include "Engine/Engine.h"
#include "MainMenuPlayerController.h"
#include "Components/TextBlock.h"
#include "Styling/SlateColor.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!FindMatchButton) return false;
	FindMatchButton->OnClicked.AddDynamic(this, &UMainMenu::FindAMatch);
	
	return true;
}

void UMainMenu::FindAMatch()
{
	if (!MenuInterface) return;
	MenuInterface->TryJoinOrCreateGame();

	if (!PlayText) return;

	GetWorld()->GetTimerManager().SetTimer(Handle_SearchTime, this, &UMainMenu::SetSearchTimeElapsed, 0.1f, true);

	FSlateColor Color = FSlateColor::FSlateColor(FLinearColor::Green);
	PlayText->SetColorAndOpacity(Color);
}

void UMainMenu::SetSearchTimeElapsed()
{
	// Setting SearchTime To Two Decimal Place
	SearchTime += 0.1;
	SearchTime = SearchTime * 10;
	SearchTime = FMath::RoundToFloat(SearchTime);
	SearchTime = SearchTime / 10;

	TArray<FStringFormatArg> Arg;
	Arg.Add(FStringFormatArg(FString(TEXT("Searching..."))));
	Arg.Add(FStringFormatArg(FString::SanitizeFloat(SearchTime, 1)));
	FString String = FString::Format(TEXT("{0} {1}"), Arg);
	PlayText->SetText(FText::FromString(String));
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuToInterface)
{
	this->MenuInterface = MenuToInterface;
}

void UMainMenu::Setup()
{
	AMainMenuPlayerController* PC = Cast<AMainMenuPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(this->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputModeData);
		PC->bShowMouseCursor = true;
	}
}

void UMainMenu::TearDown(APlayerController* PlayerController)
{
	this->RemoveFromViewport();
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
	GetWorld()->GetTimerManager().ClearTimer(Handle_SearchTime);
}