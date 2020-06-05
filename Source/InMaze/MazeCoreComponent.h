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
	void SpawnWalls(FVector const & FloorPosition);

	UFUNCTION(BlueprintCallable)
	int GetSize();

	UFUNCTION(BlueprintCallable)
	void SpawnArena(int PlayerCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SizeOfMaze = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Cells Params")
	float CellSize = 400;

	UPROPERTY(EditDefaultsOnly, Category = "Arena")
	TSubclassOf<AActor> WallToSpawn;
	UPROPERTY(EditAnywhere, Category = "Arena")
	TSubclassOf<AActor> FloorToSpawn;
	UPROPERTY(EditAnywhere, Category = "Arena")
	TSubclassOf<AActor> CornerDecorationToSpawn;
	UPROPERTY(EditAnywhere, Category = "Arena")
	TSubclassOf<AActor> BendToSpawn;
	UPROPERTY(EditAnywhere, Category = "Arena")
	TSubclassOf<AActor> BoxToSpawn;
	UPROPERTY(EditAnywhere, Category = "Arena")
	TSubclassOf<AActor> PlugToSpawn;
	UPROPERTY(EditAnywhere, Category = "Arena")
	TSubclassOf<AActor> ArenaToSpawn;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
