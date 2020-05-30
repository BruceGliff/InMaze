// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MazeCoreComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INMAZE_API UMazeCoreComponent : public USceneComponent
{
	GENERATED_BODY()

	struct Maze* Maze_path = nullptr;
public:	
	// Sets default values for this component's properties
	UMazeCoreComponent();
	~UMazeCoreComponent();

	UFUNCTION(BlueprintCallable)
	void SetSize(int Size);

	UFUNCTION(BlueprintCallable)
	void SpawnWalls(FVector const & FloorPosition , TArray<AActor*>& in);

	UFUNCTION(BlueprintCallable)
	int GetSize();

	UPROPERTY(EditAnywhere)
	int SizeOfMaze = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Walls")
	TSubclassOf<AActor> WallToSpawn;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
