// ©Copyright DevDasTour

#include "BRSafeZone.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "BRGameStateBase.h"
#include "TimerManager.h"
#include "BattleRoyaleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "BattleRoyaleGameMode.h"
#include "BRPlayerController.h"

ABRSafeZone::ABRSafeZone()
{
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("WallMesh"));
	RootComponent = WallMesh;

	WallMesh->SetWorldScale3D(FVector(Radius, Radius, Height));
	
	SetReplicates(true);
	SetReplicateMovement(true);
	bAlwaysRelevant = true;
	SetActorHiddenInGame(true);
}

void ABRSafeZone::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		ABRGameStateBase* GS = Cast<ABRGameStateBase>(GetWorld()->GetGameState());
		if (GS)
		{
			GS->SafeZone = this;
			NextRadius = Radius * ShrinkMultiplier;
			ShrinkSpeed = (Radius - NextRadius) / ShrinkTime;

			NextLocation = GetNextLocation();
		}
	}
}

FVector ABRSafeZone::GetNextLocation()
{
	float f1 = ((Radius - NextRadius) * .5f);
	float f2 = f1 * -1.f;
	float RandomNum1 = FMath::RandRange(f2, f1);
	float RandomNum2 = FMath::RandRange(f2, f1);

	float RandomCos = FMath::Cos(FMath::RandRange(-180.f, 180.f));
	float RandomSin = FMath::Sin(FMath::RandRange(-180.f, 180.f));

	float X = RandomCos * RandomNum1;
	float Y = RandomSin * RandomNum2;

	FVector NewLocation = GetActorLocation() + FVector(X, Y, GetActorLocation().Z);

	return FVector(NewLocation.X, NewLocation.Y, GetActorLocation().Z);
}

void ABRSafeZone::EnableSafeZone()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		bIsEnabled = true;
		
		FTimerHandle Handle_SafeZoneShrink;
		GetWorldTimerManager().SetTimer(Handle_SafeZoneShrink, this, &ABRSafeZone::BeginShrinking, HoldTime, false);
	}
}

void ABRSafeZone::BeginShrinking()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		NumShrinks++;
		StartShrinkLocation = GetActorLocation();
		bIsShrinking = true;
		BeginShrinkTime = GetWorld()->TimeSeconds;
		ShrinkSpeed = (Radius - NextRadius) / ShrinkTime;
		SetActorHiddenInGame(false);
	}
}

void ABRSafeZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShrinking)
	{
		UpdateWallTransform(DeltaTime);
		if (bIsEnabled)
		{
			if (GetLocalRole() == ROLE_Authority)
			{
				DamagePlayersOutsideWall(DeltaTime);
			}
		}
	}
	else if (bIsEnabled)
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			DamagePlayersOutsideWall(DeltaTime);
		}
	}
}

void ABRSafeZone::UpdateWallTransform(float DeltaSeconds)
{
	Radius = Radius - (ShrinkSpeed * DeltaSeconds);
	SetActorScale3D(FVector(Radius, Radius, Height));
	float InterpSpeed = (StartShrinkLocation - NextLocation).Size() / ShrinkTime;
	FVector ActorNewLocation = FMath::VInterpConstantTo(GetActorLocation(), NextLocation, DeltaSeconds, InterpSpeed);
	SetActorLocation(ActorNewLocation);

	bool bReached = ((GetWorld()->TimeSeconds - BeginShrinkTime) / ShrinkTime) >= 1; // Check If Reached Next Circle
	if (HasAuthority() && bReached)
	{
		bIsShrinking = false;
		HoldTime = HoldTime * TimeMultiplier;
		NextRadius = NextRadius * ShrinkMultiplier;
		NextLocation = GetNextLocation();
		ShrinkTime = ShrinkTime * TimeMultiplier;

		if (Radius >= MinRadius)
		{
			FTimerHandle Handle_LastCircle;
			GetWorldTimerManager().SetTimer(Handle_LastCircle, this, &ABRSafeZone::BeginShrinking, HoldTime, false);
		}
		else
		{
			bFinishedShrinking = true;
		}
	}
}

void ABRSafeZone::DamagePlayersOutsideWall(float DeltaSeconds)
{
	if (bIsEnabled && NumShrinks >= 0 && !IsHidden())
	{
		ABattleRoyaleGameMode* GM = Cast<ABattleRoyaleGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			for (ABRPlayerController* PC : GM->AlivePlayerControllerList)
			{
				if (PC && !PC->bIsOnPlane)
				{
					bool bOutsideZone = this->GetHorizontalDistanceTo(PC->GetPawn()) > Radius / 2.f;
					ABattleRoyaleCharacter* PlayerPawn = Cast<ABattleRoyaleCharacter>(PC->GetPawn());
					if (PlayerPawn)
					{
						PlayerPawn->bPlayerOutsideZone = bOutsideZone;
						PlayerPawn->OnRep_PlayerOutsideZone();
						if (bOutsideZone)
						{
							UGameplayStatics::ApplyDamage(PC->GetPawn(), ZoneDamagePerSecond * DeltaSeconds, nullptr, this, DamageType);
						}
					}

				}
			}
		}
	}
}

void ABRSafeZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABRSafeZone, Radius);
	DOREPLIFETIME(ABRSafeZone, NextRadius);
	DOREPLIFETIME(ABRSafeZone, NextLocation);
	DOREPLIFETIME(ABRSafeZone, bIsEnabled);
	DOREPLIFETIME(ABRSafeZone, bIsShrinking); 
	DOREPLIFETIME(ABRSafeZone, NumShrinks); 
	DOREPLIFETIME(ABRSafeZone, StartShrinkLocation);
	DOREPLIFETIME(ABRSafeZone, bFinishedShrinking);
}