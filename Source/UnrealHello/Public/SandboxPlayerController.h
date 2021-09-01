// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALHELLO_API ASandboxPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<AActor*> pawns;
	int32 currentPawnIndex = 0;

	void ChangePawn();
};
