// ©Copyright DevDasTour


#include "PlaneBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"

APlaneBase::APlaneBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(FName("SceneComp"));
	RootComponent = SceneComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
	MeshComp->AttachTo(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo(MeshComp);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachTo(SpringArm);

	SetReplicates(true);
	SetReplicateMovement(true);
	bAlwaysRelevant = true;
}

void APlaneBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetLocalRole() == ROLE_Authority)
	{
		InitialLifeSpan = MapSize / FlightSpeed;

		// Setting The Center
		float RandomNumForCos = FMath::RandRange(-180.f, 180.f);
		float RandomNumbForSine = FMath::RandRange(-180.f, 180.f);
		FVector Center = FVector(FMath::Cos(RandomNumForCos), FMath::Sin(RandomNumbForSine), 0);
		Center.Normalize();
		CenterOffset = Center;

		// Setting Path  End
		FlightPathEnd = (MapSize / 2) * CenterOffset;

		// Setting Path Start
		float RandFlightPathAngle = FMath::RandRange(-15.f, 15.f);
		FRotator Rotation = FRotator(0.f, RandFlightPathAngle, 0.f);
		FVector RotateVector = Rotation.RotateVector(CenterOffset * -1);
		FlightPathStart = RotateVector * (MapSize / 2);

		// Setting Plane Location And Rotation
		FRotator ActorNewRotation = (FlightPathEnd - FlightPathStart).Rotation();
		SetActorRotation(ActorNewRotation);
		SetActorRelativeLocation(FlightPathStart);
	}
}

void APlaneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), FlightPathEnd, DeltaTime, FlightSpeed);
	NewLocation.Z = FlyHeight;
	SetActorLocation(NewLocation);
}

void APlaneBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlaneBase, FlightPathStart);
	DOREPLIFETIME(APlaneBase, FlightPathEnd);
}