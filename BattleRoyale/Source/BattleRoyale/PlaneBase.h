// ©Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaneBase.generated.h"

UCLASS()
class BATTLEROYALE_API APlaneBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaneBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* CameraComponent;

	// Plane Working Setup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AirPlane")
		float FlyHeight = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AirPlane")
		float FlightSpeed = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AirPlane")
		float MapSize = 25000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AirPlane")
		FVector CenterOffset;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "AirPlane")
		FVector FlightPathStart;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "AirPlane")
		FVector FlightPathEnd;
};
