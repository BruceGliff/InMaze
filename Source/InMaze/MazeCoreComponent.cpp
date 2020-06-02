// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCoreComponent.h"
#include "MazeAlgorithm.h"

// Sets default values for this component's properties
UMazeCoreComponent::UMazeCoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UMazeCoreComponent::~UMazeCoreComponent()
{
	if (Maze_path)
		delete Maze_path;
}


// Called when the game starts
void UMazeCoreComponent::BeginPlay()
{
	Super::BeginPlay();

	Maze_path = new Maze{ SizeOfMaze, SizeOfMaze };
	UE_LOG(LogTemp, Warning, TEXT("Current maze size= %d"), SizeOfMaze);
	// ...
	
}

void UMazeCoreComponent::SetSize(int Size)
{
	//Maze_path = new Maze{ Size, Size };
	//UE_LOG(LogTemp, Warning, TEXT("%d"), Size);
}

void UMazeCoreComponent::SpawnWalls(FVector const & FloorPosition, TArray<AActor *> & in)
{
	TArray<AActor*> array;

	for (int i = 0; i != (SizeOfMaze + 1) * (SizeOfMaze + 1); ++i)
	{
		switch ((*Maze_path)[i])
		{
		case Maze::EPosition::NOTHING:
			break;
		case Maze::EPosition::DOWN:
		{
			FRotator rot{0,0,0};
			rot.Yaw = 90.f;
			FVector pos{ FloorPosition };
			pos.X += (i % (SizeOfMaze + 1)) * CellSize;
			pos.Y += (i / (SizeOfMaze + 1)) * CellSize - CellSize;
			array.Add(GetWorld()->SpawnActor<AActor>(WallToSpawn, pos, rot));
			break;
		}
		case Maze::EPosition::RIGHT:
		{
			FRotator rot{0,0,0};
			FVector pos{ FloorPosition };
			pos.X += (i % (SizeOfMaze + 1)) * CellSize;
			pos.Y += (i / (SizeOfMaze + 1)) * CellSize;
			array.Add(GetWorld()->SpawnActor<AActor>(WallToSpawn, pos, rot));
			break;
		}
		case Maze::EPosition::BOTH:
		{
			FRotator rot{0,0,0};
			FVector pos{ FloorPosition };
			pos.X += (i % (SizeOfMaze + 1)) * CellSize;
			pos.Y += (i / (SizeOfMaze + 1)) * CellSize;
			array.Add(GetWorld()->SpawnActor<AActor>(WallToSpawn, pos, rot));
			pos.Y -= CellSize;
			rot.Yaw = 90.f;
			array.Add(GetWorld()->SpawnActor<AActor>(WallToSpawn, pos, rot));
			break;
		}
		default:
			UE_LOG(LogTemp, Error, TEXT("ERROR index= %d"), i);
			return;
			break;
		}
	}

}

int UMazeCoreComponent::GetSize()
{
	return SizeOfMaze;
}

void UMazeCoreComponent::SpawnArena(int PlayerCount)
{
	int OneDimensionSize = static_cast<int>(sqrt(PlayerCount));

	FVector location{ 0.f, 0.f, 0.f };

	for (int i = 0; i != PlayerCount; ++i)
	{
		int const row = i / OneDimensionSize;
		int const col = i % OneDimensionSize;

		float const distant_of_arenas = 500.f;
		float const delta = CellSize * SizeOfMaze + distant_of_arenas;

		location.X = col * delta;
		location.Y = row * delta;

		GetWorld()->SpawnActor<AActor>(ArenaToSpawn, location, FRotator{ 0.f, 0.f, 0.f });
	}


}