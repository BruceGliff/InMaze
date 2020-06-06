// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Construction_base.generated.h"

UCLASS()
class INMAZE_API AConstruction_base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConstruction_base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* Spawn(UWorld* World, FVector const& Position, FRotator const& Rotation) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "An Object")
	TSubclassOf<AActor> ActorToSpawn;
};
