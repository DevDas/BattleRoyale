// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BRSafeZone.generated.h"

UCLASS()
class BATTLEROYALE_API ABRSafeZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABRSafeZone();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SafeZone")
		float Height = 15000;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "SafeZone", meta = (InstanceEditable = "true"))
		float Radius = 40000;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "SafeZone", meta = (InstanceEditable = "true"))
		float NextRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SafeZone", meta = (InstanceEditable = "true"))
		float MinRadius = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SafeZone", meta = (InstanceEditable = "true"))
		float ShrinkMultiplier = 0.8f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SafeZone", meta = (InstanceEditable = "true"))
		float ShrinkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SafeZone", meta = (InstanceEditable = "true"))
		float ShrinkTime = 40.f;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "SafeZone", meta = (InstanceEditable = "true"))
		FVector NextLocation;

	UFUNCTION(BlueprintPure)
		FVector GetNextLocation();

	UFUNCTION(BlueprintCallable)
		void EnableSafeZone();

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "SafeZone")
		bool bIsEnabled;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "SafeZone")
		bool bIsShrinking;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "SafeZone")
		bool bFinishedShrinking;

	UFUNCTION(BlueprintCallable)
		void BeginShrinking();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SafeZone")
		float HoldTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SafeZone")
		float TimeMultiplier = 0.8;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "SafeZone")
		int32 NumShrinks;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "SafeZone")
		FVector StartShrinkLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SafeZone")
		float BeginShrinkTime;

	UFUNCTION(BlueprintCallable)
		void UpdateWallTransform(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
		void DamagePlayersOutsideWall(float DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneDamage")
		TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneDamage")
		float ZoneDamagePerSecond = 5.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* WallMesh;

};
