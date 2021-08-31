// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	initLocation = GetActorLocation();

	//printTypes();
	//printStringTypes();

	setColor(geometryData.color);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	handleMovement();
}

void ABaseGeometryActor::printTypes()
{
	UE_LOG(LogBaseGeometry, Warning, L"Actor name: %s", *GetName());
	UE_LOG(LogBaseGeometry, Warning, L"Weapons %d", weaponsNum);
	UE_LOG(LogBaseGeometry, Warning, L"Health %f", health);
	UE_LOG(LogBaseGeometry, Warning, L"Is dead %d", isDead);
	UE_LOG(LogBaseGeometry, Warning, L"Has weapon %d", hasWeapon)
}

void ABaseGeometryActor::printStringTypes() {

	FString weapons = "Weapons=" + FString::FromInt(5);
	FString healthStr = "Health=" + FString::SanitizeFloat(1.23F);
	FString isDeadStr = "Is dead=" + FString(isDead ? "true" : "false");
	FString stat = FString::Printf(TEXT("All %s %s %s"), *weapons, *healthStr, *isDeadStr);
	UE_LOG(LogBaseGeometry, Warning, L"%s", *stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("John Connor"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, stat, true, FVector2D(1.5F));
}

void ABaseGeometryActor::printTransform()
{
	FTransform transform = GetActorTransform();
	FVector location = transform.GetLocation();
	FRotator rotation = transform.Rotator();
	FVector scale = transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, L"Actor name: %s", *GetName());
	UE_LOG(LogBaseGeometry, Warning, L"Transform %s", *transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, L"Location %s", *location.ToString());
	UE_LOG(LogBaseGeometry, Warning, L"Rotator %s", *rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, L"Scale %s", *scale.ToString());

	UE_LOG(LogBaseGeometry, Error, L"Human Transform %s", *transform.ToHumanReadableString());

}

void ABaseGeometryActor::handleMovement()
{
	switch (geometryData.moveType)
	{
		case EMovementType::Sin: {
			FVector curLocation = GetActorLocation();
			float time = GetWorld()->GetTimeSeconds();
			curLocation.Z = initLocation.Z + geometryData.amplitude * FMath::Sin(geometryData.frequency * time);
			SetActorLocation(curLocation);
			break;
		}
		case EMovementType::Static: break;
		default:
			break;
	}
}

void ABaseGeometryActor::setColor(const FLinearColor& color)
{
	UMaterialInstanceDynamic* dynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (dynMaterial) {
		dynMaterial->SetVectorParameterValue("Color", color);
	}
}
