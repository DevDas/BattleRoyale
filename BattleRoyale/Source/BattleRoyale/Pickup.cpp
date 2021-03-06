// ©Copyright DevDasTour

#include "Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BattleRoyaleCharacter.h"
#include "PickupHealth.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->AttachTo(RootComponent);

	SphereComp->SetSimulatePhysics(true);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetReplicates(true);
}

void APickup::Test()
{
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.AddDynamic(this, &APickup::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APickup::BeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &APickup::EndOverlap);
}

void APickup::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SphereComp->SetSimulatePhysics(false);
}

void APickup::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABattleRoyaleCharacter* PlayerPawn = Cast<ABattleRoyaleCharacter>(OtherActor);
	if (PlayerPawn)
	{
		PickupEntered(PlayerPawn);
	}
}

void APickup::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABattleRoyaleCharacter* PlayerPawn = Cast<ABattleRoyaleCharacter>(OtherActor);
	if (PlayerPawn)
	{
		PickupLeft(PlayerPawn);
	}
}

void APickup::PickupEntered(ABattleRoyaleCharacter* Character)
{
	PickupEnteredEvent(Character);
}

void APickup::PickupLeft(ABattleRoyaleCharacter* Character)
{
	PickupLeftEvent(Character);
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}