// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryPlayerComponent, All, All)

void ASandboxPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	if (InputComponent) {
		InputComponent->BindAction("ChangePawn", EInputEvent::IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
	}
}

void ASandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), pawns);
}

void ASandboxPlayerController::ChangePawn()
{
	if (pawns.Num() <= 1) return;

	UE_LOG(LogGeometryPlayerComponent, Display, L"CHANGE PAWN");

	ASandboxPawn* currentPawn = Cast<ASandboxPawn>(pawns[currentPawnIndex]);
	currentPawnIndex = (currentPawnIndex + 1) % pawns.Num();

	if (!currentPawn) return;

	Possess(currentPawn);
}
