// Fill out your copyright notice in the Description page of Project Settings.


#include "Construction_Floor.h"

AConstruction_Floor::AConstruction_Floor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConstruction_Floor::BeginPlay()
{
	Super::BeginPlay();
}

AActor* AConstruction_Floor::Spawn(UWorld* World, FVector const& Position) const
{
	return AConstruction_base::Spawn(World, Position, FRotator{ 0.f, 0.f, 0.f });
}

// Called every frame
void AConstruction_Floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

