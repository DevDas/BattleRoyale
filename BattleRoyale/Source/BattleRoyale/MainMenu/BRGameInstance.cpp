// ©Copyright DevDasTour

#include "BRGameInstance.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = TEXT("NAME_GameSession");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

UBRGameInstance::UBRGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/UI/WBP_MainMenu"));
	if (!MainMenuBPClass.Class) return;
	MainMenuClass = MainMenuBPClass.Class;
}

void UBRGameInstance::Init()
{
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem)
	{
		UEngine* Engine = GetEngine();
		if (!Engine) return;
		Engine->AddOnScreenDebugMessage(0, 60, FColor::Blue, FString::Printf(TEXT("Found SubSystem : %s"), *SubSystem->GetSubsystemName().ToString()));
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem : %s"), *SubSystem->GetSubsystemName().ToString())

		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UBRGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UBRGameInstance::OnJoinSessionComplete);
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UBRGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UBRGameInstance::OnDestroySessionComplete);
		}
	}
}

void UBRGameInstance::OnFindSessionComplete(bool Success)
{
	if (Success)
	{
		if (SessionSearch.IsValid())
		{
			if (SessionSearch->SearchResults.Num() > 0)
			{
				FOnlineSessionSearchResult SearchResult = SessionSearch->SearchResults[0];

				if (SearchResult.IsValid())
				{
					JoinSession(SearchResult);
				}
				UE_LOG(LogTemp, Warning, TEXT("Found A Session"))
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Can't Find A Session"))
				CreateSession();
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Find Session Complete!!!"))
	}
	else
	{
		CreateSession();
	}
}

void UBRGameInstance::JoinSession(FOnlineSessionSearchResult SearchResult)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;
	
	// TODO TearDown Menu
	SessionInterface->JoinSession(0, SESSION_NAME, SearchResult);
}

void UBRGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;
	FString Address;
	bool bGotConnection = SessionInterface->GetResolvedConnectString(SessionName, Address);
	if (!bGotConnection)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't Get the Connection String"))
	}

	APlayerController* PC = GetFirstLocalPlayerController();
	if (PC)
	{
		UEngine* Engine = GetEngine();
		if (!Engine) return;
		Engine->AddOnScreenDebugMessage(0, 10, FColor::Yellow, FString::Printf(TEXT("Joining : %s"), *Address));
		MainMenu->TearDown(PC);

		PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UBRGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			FString DesiredServerName = TEXT("BattleRoyale");
			FOnlineSessionSettings SessionSettings;
			if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" || bUseLan)
			{
				SessionSettings.bIsLANMatch = true;
			}
			else
			{
				SessionSettings.bIsLANMatch = false;
			}
			SessionSettings.NumPublicConnections = NumberOfPlayers;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bUsesPresence = true;
			SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

			SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
		}
	}
}

void UBRGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't Creat The Session"))
		return;
	}
	if (MainMenu)
	{
		APlayerController* PC = GetFirstLocalPlayerController();
		if (PC)
		{
			MainMenu->TearDown(PC);
		}
	}
	UEngine* Engine = GetEngine();
	if (!Engine) return;
	Engine->AddOnScreenDebugMessage(0, 10, FColor::Green, TEXT("Hosting A Game"));

	GetWorld()->ServerTravel("/Game/_Level/Map?listen");
}

void UBRGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

void UBRGameInstance::TryJoinOrCreateGame()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = bUseLan;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->MaxSearchResults = 100;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UBRGameInstance::LoadMainMenu()
{
	if (!MainMenuClass) return;
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (!MainMenu) return;
	MainMenu->AddToViewport();
	MainMenu->SetMenuInterface(this);
	MainMenu->Setup();
}