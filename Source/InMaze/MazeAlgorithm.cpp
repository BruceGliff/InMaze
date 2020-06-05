// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeAlgorithm.h"

#include <ctime>
#include <cstring>

enum class EDirection
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	ALL
};

int get_random();

Maze::Maze(int vert, int horiz) :
	vertical_(vert),
	horizontal_(horiz)
{
	cell_ = new Cell * [vert];
	intermediate_array = new int[horiz];

	for (int i = 0; i < vert; i++)
		cell_[i] = new Cell[horiz];

	Construct();
}

void Maze::Construct() noexcept
{
	for (int j = 0; j < horizontal_; j++)
	{
		cell_[0][j].set_ = j;
		cell_[0][j].north_ = Cell::WALL;
	}

	// begin

	for (int i = 0; i < vertical_; i++)
	{
		cell_[i][0].west_ = Cell::WALL;
		cell_[i][horizontal_ - 1].east_ = Cell::WALL;



		for (int j = 0; j < horizontal_ - 1; j++)
		{
			if (cell_[i][j].set_ != cell_[i][j + 1].set_)
				if (get_random() % 3 == 1)
				{
					cell_[i][j].east_ = Cell::WALL;
					cell_[i][j + 1].west_ = Cell::WALL;
				}

				else
					cell_[i][j + 1].set_ = cell_[i][j].set_;

			else
			{
				cell_[i][j].east_ = Cell::WALL;
				cell_[i][j + 1].west_ = Cell::WALL;
			}
		}

		bool was_opened_cell = false;

		for (int j = 0; j < horizontal_ - 1; j++)
		{

			if ((cell_[i][j].set_ != cell_[i][j + 1].set_ && was_opened_cell == true) || (cell_[i][j].set_ == cell_[i][j + 1].set_))
				if (get_random() % 3 == 1)
				{
					cell_[i][j].south_ = Cell::WALL;

					if (i + 1 < vertical_)
						cell_[i + 1][j].north_ = Cell::WALL;
				}
				else
					was_opened_cell = true;
			else
				was_opened_cell = true;


			if (cell_[i][j].set_ != cell_[i][j + 1].set_)
				was_opened_cell = false;
		}

		if (was_opened_cell)
			if (get_random() % 3 == 1)
			{
				cell_[i][horizontal_ - 1].south_ = Cell::WALL;

				if (i + 1 < vertical_)
					cell_[i + 1][horizontal_ - 1].north_ = Cell::WALL;
			}


		if (i + 1 != vertical_)
		{

			for (int j = 0; j < horizontal_; j++)
			{
				cell_[i + 1][j].south_ = cell_[i][j].south_;
				cell_[i + 1][j].east_ = cell_[i][j].east_;
				cell_[i + 1][j].west_ = cell_[i][j].west_;
				cell_[i + 1][j].set_ = cell_[i][j].set_;
			}

			change_array_before_start(cell_, i + 1, horizontal_);
		}
	}

	last_line_processing(cell_[vertical_ - 1], horizontal_);

	placement = convert();
}

Maze::~Maze()
{
	for (int i = 0; i < vertical_; i++)
		delete[] cell_[i];

	delete[] cell_;
	delete[] intermediate_array;
	if (placement)
	{
		for (int i = 0; i != vertical_ + 1; ++i)
			delete[] placement[i];
		delete[] placement;
	}
}

Cell_Improved const & Maze::At(int i, int j) const noexcept
{
	return placement[i][j];
}

int get_random()
{
	static int a = 0;
	a += int(time(NULL));
	a -= 56; // my random number
	a %= 124;
	return a;
}

int Maze::change_array_before_start(Cell** array, int number, int range)
{
	memset(intermediate_array, 0, horizontal_ * sizeof(int));

	for (int i = 0; i < range; i++)
	{
		if (i > 0)
			array[number][i].delete_wall(EDirection::WEST);
		if (i < range - 1)
			array[number][i].delete_wall(EDirection::EAST);

		if (array[number][i].check_wall(EDirection::SOUTH))
		{
			array[number][i].set_ = -1;
			array[number][i].south_ = Cell::NO_WALL;

			if (number < vertical_ - 1)
				array[number + 1][i].north_ = Cell::NO_WALL;
		}
		else
			intermediate_array[array[number][i].set_] = 1;
	}

	int set_number = 0;
	for (int i = 0; i < range; i++)
		if (array[number][i].set_ == -1)
		{
			while (intermediate_array[set_number] != 0)
				set_number++;
			array[number][i].set_ = set_number;

			intermediate_array[set_number] = 1;
		}

	return 0;
}


int Maze::last_line_processing(Cell* array, int range)
{
	int prev = array[0].set_;

	for (int i = 0; i < range - 1; i++)
	{
		if (prev != array[i + 1].set_)
		{
			prev = array[i + 1].set_;
			array[i + 1].set_ = array[i].set_;
			array[i + 1].delete_wall(EDirection::WEST);
			array[i].delete_wall(EDirection::EAST);
		}

		array[i].south_ = Cell::WALL;
	}

	array[range - 1].south_ = Cell::WALL;
	return 0;
}


int Cell::delete_wall(EDirection dir)
{
	switch (dir)
	{
	case EDirection::SOUTH:
		south_ = NO_WALL;
		break;
	case EDirection::NORTH:
		north_ = NO_WALL;
		break;
	case EDirection::EAST:
		east_ = NO_WALL;
		break;
	case EDirection::WEST:
		west_ = NO_WALL;
		break;
	case EDirection::ALL:
		south_ = NO_WALL;
		north_ = NO_WALL;
		east_ = NO_WALL;
		west_ = NO_WALL;
		break;
	}

	return 0;
}
bool Cell::check_wall(EDirection dir)
{
	switch (dir)
	{
	case EDirection::SOUTH:
		if (south_ == WALL)
			return true;
		break;
	case EDirection::NORTH:
		if (north_ == WALL)
			return true;
		break;
	case EDirection::EAST:
		if (east_ == WALL)
			return true;
		break;
	case EDirection::WEST:
		if (west_ == WALL)
			return true;
		break;
	}

	return false;
}

Cell_Improved ** Maze::convert()
{
	Cell_Improved** cells = new(std::nothrow) Cell_Improved * [vertical_ + 1];
	if (!cells)
		return nullptr;
	for (int i = 0; i != vertical_ + 1; ++i)
	{
		cells[i] = new(std::nothrow) Cell_Improved [horizontal_ + 1];
		if (!cells[i])
		{
			for (int j = 0; j != i; ++j)
				delete[] cells[j];
			delete[] cells;
		}
	}

	for (int i = 0; i != vertical_; ++i)
	{
		for (int j = 0; j != horizontal_; ++j)
		{
			Cell const& Current_cell = cell_[i][j];

			// Set up Walls
			if (Current_cell.north_)
				cells[i][j].Wall_position[0] = 1;
			if (Current_cell.west_)
				cells[i][j].Wall_position[1] = 1;

			// Set up corner decoration
			cells[i][j].CornerDecoration_position[0] = Current_cell.north_ & Current_cell.west_;
			cells[i][j].CornerDecoration_position[1] = Current_cell.north_ & Current_cell.east_;
			cells[i][j].CornerDecoration_position[2] = Current_cell.south_ & Current_cell.west_;
			cells[i][j].CornerDecoration_position[3] = Current_cell.south_ & Current_cell.east_;

			// Set up face decoration
			if (Current_cell.north_)
			{
				if ( (j != 0) && (cell_[i][j - 1].north_) )
				{
					cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Box;
					continue;
				}
				if ( (i != 0) && (cell_[i - 1][j].west_) && (i != vertical_ - 1) && (cell_[i + 1][j].west_) )
				{
					cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Box;
					continue;
				}
				if ( (i != vertical_ - 1) && (cell_[i + 1][j].west_) )
				{
					cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Bend_DownRight;
					continue;
				}
				if ( (i != 0) && (cell_[i - 1][j].west_) )
				{
					cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Bend_UpRight;
					continue;
				}
				cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Plug_Left;
				continue;
			}
			if (Current_cell.west_)
			{
				if ((i != 0) && (cell_[i - 1][j].west_))
				{
					cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Box;
					continue;
				}
				if ((j != 0) && (cell_[i][j - 1].north_))
				{
					cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Bend_DownLeft;
					continue;
				}
				cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Plug_Up;
				continue;
			}

			if ((j != 0) && (i != 0) && (cell_[i - 1][j].west_) && (cell_[i][j - 1].north_))
			{
				cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Bend_UpLeft;
				continue;
			}
			if ((j != 0) && (cell_[i][j - 1].north_))
			{
				cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Plug_Right;
				continue;
			}
			if ((i != 0) && (cell_[i - 1][j].west_))
			{
				cells[i][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Plug_Down;
				continue;
			}
		}
		cells[i][horizontal_].Wall_position[1] = 1;
		cells[i][horizontal_].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Box;
	}

	for (int j = 0; j != horizontal_; ++j)
	{
		cells[vertical_][j].Wall_position[0] = 1;
		cells[vertical_][j].FaceDecoration_position = Cell_Improved::EFaceDecorationType::Box;
	}

	return cells;
}