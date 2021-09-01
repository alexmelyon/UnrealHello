// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

// Sets default values
ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(sceneComponent);

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	staticMeshComponent->SetupAttachment(sceneComponent);
	cameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	cameraComponent->SetupAttachment(GetRootComponent());
}

void ASandboxPawn::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);

	if (!controller) return;

	UE_LOG(LogSandboxPawn, Error, L"%s POSSESSED BY %s", *GetName(), *controller->GetName());
}

void ASandboxPawn::UnPossessed()
{
	Super::UnPossessed();

	UE_LOG(LogSandboxPawn, Warning, L"%s UNPOSSESSED", *GetName());
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

	if (!velocityVector.IsZero() && IsControlled()) {
		const FVector newLoc = GetActorLocation() + velocity * DeltaTime * velocityVector;
		SetActorLocation(newLoc);
		velocityVector = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent) {
		PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
	}
}

void ASandboxPawn::MoveForward(float amount)
{
	velocityVector.X = amount;
}

void ASandboxPawn::MoveRight(float amount)
{
	velocityVector.Y = amount;
}

