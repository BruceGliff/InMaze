// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Construction_base.h"
#include "Construction_Floor.generated.h"

/**
 * 
 */
UCLASS()
class INMAZE_API AConstruction_Floor : public AConstruction_base
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConstruction_Floor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* Spawn(UWorld* World, FVector const& Position) const;
	
};
