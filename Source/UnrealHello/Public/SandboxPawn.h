// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

class UCameraComponent;

UCLASS()
class UNREALHELLO_API ASandboxPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASandboxPawn();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* sceneComponent;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* staticMeshComponent;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* cameraComponent;

	UPROPERTY(EditAnywhere)
	float velocity = 300.0F;

	virtual void PossessedBy(AController* controller) override;
	virtual void UnPossessed() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector velocityVector = FVector::ZeroVector;

	void MoveForward(float amount);
	void MoveRight(float amount);
};
