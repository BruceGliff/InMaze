// Fill out your copyright notice in the Description page of Project Settings.
#include "MazeCoreComponent.h"

#include <vector>
#include "MazeAlgorithm.h"
#include "GameFramework/PlayerStart.h"

// Sets default values for this component's properties
UMazeCoreComponent::UMazeCoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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

void UMazeCoreComponent::SpawnWalls(FVector const & FloorPosition)
{
	TArray<AActor*> array;
	array.Reserve((SizeOfMaze + 1) * (SizeOfMaze + 1) * 5);

	UWorld* World = GetWorld();
	if (!World)
		return;

	int const Size_pow2 = SizeOfMaze * SizeOfMaze;

	std::vector<int> SpawnShape{ Size_pow2 };
	SpawnShape.assign(Size_pow2, 0);

	int CurrentSpawnsCount = 0;
	while (CurrentSpawnsCount != NumberOfPlayers)
	{
		int rand = FMath::RandRange(0, Size_pow2);
		if (!SpawnShape[rand])
		{
			SpawnShape[rand] = 1;
			++CurrentSpawnsCount;
		}
	}

	for (int i = 0; i != SizeOfMaze * SizeOfMaze; ++i)
	{
		int const col = i % SizeOfMaze;
		int const row = i / SizeOfMaze;

		FVector const floorPosition{ FloorPosition + FVector{col * CellSize, row * CellSize, 0} };
		AActor * Spawned = World->SpawnActor<AActor>(FloorToSpawn, floorPosition, FRotator{0.f, 0.f, 0.f});
		if (SpawnShape[i])
		{
			FVector const SpawnPosition{ floorPosition + FVector{CellSize / 2, CellSize / 2, 0.f} };
			//AActor* SpawnPoint = World->SpawnActor<APlayerStart>(SpawnPosition, FRotator{ 0.f, 0.f, 0.f });
			AActor* SpawnPoint = World->SpawnActor<AActor>(CharactersToSpawn, SpawnPosition, FRotator{ 0.f, 0.f, 0.f });
		}
	}


	for (int i = 0; i != SizeOfMaze + 1; ++i)
	{
		for (int j = 0; j != SizeOfMaze + 1; ++j)
		{
			Cell_Improved const& Current_cell = Maze_path->At(i, j);

			FVector const pos{ FloorPosition + FVector{j * CellSize, i * CellSize, 0} };

			if (Current_cell.Wall_position[0])
			{
				FRotator rot{ 0.f, 0.f, 0.f };
				array.Add(World->SpawnActor<AActor>(WallToSpawn, pos, rot));
			}
			if (Current_cell.Wall_position[1])
			{
				FRotator rot{ 0.f, 0.f, 0.f };
				rot.Yaw = 90.f;
				array.Add(World->SpawnActor<AActor>(WallToSpawn, pos, rot));
			}

			for (int k = 0; k != 4; ++k)
			{
				if (Current_cell.CornerDecoration_position[k])
				{
					FRotator rot{ 0.f, 0.f, 0.f };
					rot.Yaw = 90.f * (k % 2) - 90.f * (k / 2);
					if (k == 3)
						rot.Yaw = 180.f;
					array.Add(World->SpawnActor<AActor>(CornerDecorationToSpawn, pos + FVector{ CellSize * (k % 2), CellSize * (k / 2), 0.f}, rot));
				}
			}

			switch (Current_cell.FaceDecoration_position)
			{
			case Cell_Improved::EFaceDecorationType::Bend_DownLeft:
			{
				FRotator const rot{ 0.f, 90.f, 0.f };
				array.Add(World->SpawnActor<AActor>(BendToSpawn, pos, rot));
				break;
			}
			case Cell_Improved::EFaceDecorationType::Bend_DownRight:
			{
				FRotator const rot{ 0.f, 0.f, 0.f };
				array.Add(World->SpawnActor<AActor>(BendToSpawn, pos, rot));
				break;
			}
			case Cell_Improved::EFaceDecorationType::Bend_UpLeft:
			{
				FRotator const rot{ 0.f, 180.f, 0.f };
				array.Add(World->SpawnActor<AActor>(BendToSpawn, pos, rot));
				break;
			}
			case Cell_Improved::EFaceDecorationType::Bend_UpRight:
			{
				FRotator const rot{ 0.f, 270.f, 0.f };
				array.Add(World->SpawnActor<AActor>(BendToSpawn, pos, rot));
				break;
			}
			case Cell_Improved::EFaceDecorationType::Box:
			{
				FRotator const rot{ 0.f, 0.f, 0.f };
				array.Add(World->SpawnActor<AActor>(BoxToSpawn, pos, rot));
				break;
			}
			case Cell_Improved::EFaceDecorationType::Plug_Down:
			{
				FRotator const rot{ 0.f, 270.f, 0.f };
				array.Add(World->SpawnActor<AActor>(PlugToSpawn, pos, rot));
				break;
			}
			case Cell_Improved::EFaceDecorationType::Plug_Left:
			{
				FRotator const rot{ 0.f, 0.f, 0.f };
				array.Add(World->SpawnActor<AActor>(PlugToSpawn, pos, rot));
				break;
			}
			case Cell_Improved::EFaceDecorationType::Plug_Right:
			{
				FRotator const rot{ 0.f, 180.f, 0.f };
				array.Add(World->SpawnActor<AActor>(PlugToSpawn, pos, rot));
				break;
			}
			case Cell_Improved::EFaceDecorationType::Plug_Up:
			{
				FRotator const rot{ 0.f, 90.f, 0.f };
				array.Add(World->SpawnActor<AActor>(PlugToSpawn, pos, rot));
				break;
			}
			}
		}
	}

}

int UMazeCoreComponent::GetSize()
{
	return SizeOfMaze;
}

void UMazeCoreComponent::SpawnArena(int PlayerCount)
{
	UWorld* World = GetWorld();
	if (!World)
		return;

	NumberOfPlayers = PlayerCount;
	int OneDimensionSize = static_cast<int>(sqrt(PlayerCount));

	FVector location{ 0.f, 0.f, 0.f };

	for (int i = 0; i != 1; ++i)
	{
		int const row = i / OneDimensionSize;
		int const col = i % OneDimensionSize;

		float const distant_of_arenas = 500.f;
		float const delta = CellSize * SizeOfMaze + distant_of_arenas;

		location.X = col * delta;
		location.Y = row * delta;

		World->SpawnActor<AActor>(ArenaToSpawn, location, FRotator{ 0.f, 0.f, 0.f });
	}


}
