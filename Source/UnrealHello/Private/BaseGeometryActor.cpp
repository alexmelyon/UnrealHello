// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	printTypes();
	printStringTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGeometryActor::printTypes()
{
	UE_LOG(LogTemp, Warning, L"INT %d", 123);
	UE_LOG(LogTemp, Warning, TEXT("FLOAT %f"), 123.0F);
	UE_LOG(LogTemp, Warning, L"BOOL %d", true);
}

void ABaseGeometryActor::printStringTypes() {

	FString weapons = "Weapons=" + FString::FromInt(5);
	FString health = "Health=" + FString::SanitizeFloat(1.23F);
	bool isDead = false;
	FString isDeadStr = "Is dead=" + FString(isDead ? "true" : "false");
	FString stat = FString::Printf(TEXT("All %s %s %s"), *weapons, *health, *isDeadStr);
	UE_LOG(LogBaseGeometry, Warning, L"%s", *stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("John Connor"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, stat, true, FVector2D(1.5F));
}