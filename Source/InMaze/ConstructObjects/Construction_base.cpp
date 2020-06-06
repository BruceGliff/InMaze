// Fill out your copyright notice in the Description page of Project Settings.


#include "Construction_base.h"

#include "Engine/World.h"
#include "Components/SceneComponent.h"

// Sets default values
AConstruction_base::AConstruction_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AConstruction_base::BeginPlay()
{
	Super::BeginPlay();
	
}

AActor* AConstruction_base::Spawn(UWorld* World, FVector const& Position, FRotator const& Rotation) const
{
	if (!World)
		return nullptr;

	return World->SpawnActor<AActor>(ActorToSpawn, Position, Rotation);
}

// Called every frame
void AConstruction_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

