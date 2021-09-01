// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	//DoActorSpawn1();
	//DoActorSpawn2();
	//DoActorSpawn3();
	DoActorSpawn4();
}

void AGeometryHubActor::DoActorSpawn3() {
	UWorld* world = GetWorld();
	if (world) {
		for (const FGeometryPayload payload : geometryPayloads) {
			ABaseGeometryActor* actor = world->SpawnActorDeferred<ABaseGeometryActor>(payload.geometryClass, payload.initTransform);
			if (actor) {
				FGeometryData data = payload.data;
				actor->setGeometryData(data);
				actor->onColorChanged.AddDynamic(this, &AGeometryHubActor::onColorChanged);
				actor->onTimerFinished.AddUObject(this, &AGeometryHubActor::onTimerFinished);
				actor->FinishSpawning(payload.initTransform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2() {
	UWorld* world = GetWorld();
	if (world) {
		for (int32 i = 0; i < 10; ++i) {
			FTransform geometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0F, 300.0F * i, 700.0F));
			ABaseGeometryActor* geometry = world->SpawnActorDeferred<ABaseGeometryActor>(geometryClass, geometryTransform);
			if (geometry) {
				FGeometryData data;
				data.color = FLinearColor::MakeRandomColor();
				geometry->setGeometryData(data);
				geometry->FinishSpawning(geometryTransform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn1() {

	UWorld* world = GetWorld();
	if (world) {
		for (int32 i = 0; i < 10; ++i) {
			FTransform geometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0F, 300.0F * i, 300.0F));
			ABaseGeometryActor* geometry = world->SpawnActor<ABaseGeometryActor>(geometryClass, geometryTransform);
			if (geometry) {
				FGeometryData data;
				data.moveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				geometry->setGeometryData(data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn4()
{
	if (!GetWorld()) return;

	FTransform geometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0F, 300.0F, 300.0F));
	nonPropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(geometryClass, geometryTransform);

	geometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0F, 700.0F, 300.0F));
	propertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(geometryClass, geometryTransform);
}

void AGeometryHubActor::onColorChanged(const FLinearColor& color, const FString& name)
{
	UE_LOG(LogGeometryHub, Warning, L"Actor %s color %s", *name, *color.ToString());
}

void AGeometryHubActor::onTimerFinished(AActor* actor)
{
	if (!actor) return;

	UE_LOG(LogGeometryHub, Error, L"Timer finished %s", *actor->GetName());

	ABaseGeometryActor* geometry = Cast<ABaseGeometryActor>(actor);
	if (!geometry) return;

	UE_LOG(LogGeometryHub, Display, L"Cast successful; amplitude=%f", geometry->getGeometryData().amplitude);
	geometry->Destroy();
	//geometry->SetLifeSpan(2.0F);
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogGeometryHub, Warning, L"Property pointer=%i isValid=%i", propertyActor != nullptr, IsValid(propertyActor));
	UE_LOG(LogGeometryHub, Warning, L"Nonproperty pointer=%i isValid=%i", nonPropertyActor != nullptr, IsValid(nonPropertyActor));
}

