// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"
#include "Components/InputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

// Sets default values
ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(sceneComponent);
}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!velocityVector.IsZero()) {
		const FVector newLoc = GetActorLocation() + velocity * DeltaTime * velocityVector;
		SetActorLocation(newLoc);
	}
}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
}

void ASandboxPawn::MoveForward(float amount)
{
	UE_LOG(LogSandboxPawn, Display, L"Move forward %f", amount);

	velocityVector.X = amount;
}

void ASandboxPawn::MoveRight(float amount)
{
	UE_LOG(LogSandboxPawn, Display, L"Move right %f", amount);

	velocityVector.Y = amount;
}

