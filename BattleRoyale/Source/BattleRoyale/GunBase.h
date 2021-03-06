// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class BATTLEROYALE_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	float Damage = 30.f;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	FString WeaponName = TEXT("Weapon");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	class USkeletalMeshComponent* FirstPersonGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	class USkeletalMeshComponent* ThirdPersonGun;

	// Ammo 
	UPROPERTY(EditAnywhere,Replicated, BlueprintReadWrite, Category = "WeaponInfo", meta = (ExposeOnSpawn = "true"), meta = (InstanceEditable = "true"))
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "WeaponInfo", meta = (ExposeOnSpawn = "true"), meta = (InstanceEditable = "true"))
	int32 CurrentBagAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 StartingBagAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
		int32 ClipSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 MaxBagAmmo = 300;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "GunHolder")
	class ABattleRoyaleCharacter* CurrentOwner;

	UFUNCTION(BlueprintPure)
		bool HasAmmo() { return CurrentAmmo>0; };

	UFUNCTION(BlueprintCallable)
	void GiveAmmo(int32 AmmoToGive);

	UFUNCTION(BlueprintCallable)
		void OnFired();

	UFUNCTION(BlueprintCallable)
		void Reload();

	void ReloadAnimation();

	FTimerHandle TimerHandle_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponPickup")
	TSubclassOf<class APickupGun> WeaponPickup;
};