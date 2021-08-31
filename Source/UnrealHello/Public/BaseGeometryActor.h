// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8 {
	Sin, Static
};

USTRUCT(BlueprintType)
struct FGeometryData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float amplitude = 50.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float frequency = 2.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType moveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Design")
	float timerRateSec = 3.0F;
};

UCLASS()
class UNREALHELLO_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	void setGeometryData(const FGeometryData& data) { geometryData = data; }

	UFUNCTION(BlueprintCallable)
	FGeometryData getGeometryData() const { return geometryData; }

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged onColorChanged;
	FOnTimerFinished onTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry data")
	FGeometryData geometryData;

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
	FTimerHandle timerHandle;
	const int32 maxTimerCount = 5;
	int32 timerCount = 0;

	void printTypes();
	void printStringTypes();
	void printTransform();
	void handleMovement();
	void setColor(const FLinearColor& color);

	void onTimerFired();
};
