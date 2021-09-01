// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseGeometryActor> geometryClass;

	UPROPERTY(EditAnywhere)
		FGeometryData data;

	UPROPERTY(EditAnywhere)
		FTransform initTransform;
};

UCLASS()
class UNREALHELLO_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGeometryHubActor();

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseGeometryActor> geometryClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TArray< FGeometryPayload >geometryPayloads;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	ABaseGeometryActor* nonPropertyActor;

	UPROPERTY()
	ABaseGeometryActor* propertyActor;

	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();
	void DoActorSpawn4();

	UFUNCTION()
	void onColorChanged(const FLinearColor& color, const FString& name);
	void onTimerFinished(AActor* actor);
};
