// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

UCLASS()
class UNREALHELLO_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float amplitude = 50.0F;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float frequency = 2.0F;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 weaponsNum = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 killsNum = 7;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float health = 1.23F;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool isDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool hasWeapon = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector initLocation;
	void printTypes();
	void printStringTypes();
	void printTransform();
};
