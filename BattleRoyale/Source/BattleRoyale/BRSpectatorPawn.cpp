// ©Copyright DevDasTour


#include "BRSpectatorPawn.h"

// Sets default values
ABRSpectatorPawn::ABRSpectatorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABRSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABRSpectatorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABRSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

