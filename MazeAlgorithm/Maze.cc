#include "Maze.h"

#include <iostream>
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
	cell_ = new Cell*[vert];
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
        delete[] placement;
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
    memset(intermediate_array, 0, horizontal_);
    
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


int Maze::last_line_processing(Cell * array, int range)
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

int Maze::print_maze()
{

	for (int i = 0; i < horizontal_; i++)
		printf(" __");

	printf("\n");

	for (int i = 0; i < vertical_; i++)
	{
		printf("|");

		for (int j = 0; j < horizontal_; j++)
		{
			if (cell_[i][j].south_ == Cell::WALL)
			{
				if (i < vertical_ - 1)
					if (cell_[i + 1][j].north_ != Cell::WALL)
						printf("!!");
					else
						printf("__");
				else
					printf("__");
			}
			else
				printf("  ");

			if (cell_[i][j].check_wall(EDirection::EAST))
				printf("|");
			else
				printf(" ");
		}

		printf("\n");
	}

	return 0;
}

int * Maze::convert()
{
	int * res = new(std::nothrow) int[(vertical_ + 1) * (horizontal_ + 1)];
    if (res == nullptr)
        return res;
    
	for (int i = 0; i < (vertical_ + 1) * (horizontal_ + 1); i++)
		res[i] = 0;

	int k = 0;

	for (int i = 0; i < vertical_; i++)
	{
		for (int j = 0; j < horizontal_; j++)
		{
			if (cell_[i][j].north_ == Cell::WALL)
			{

				if (i > 0)
					if (cell_[i - 1][j].south_ != Cell::WALL)
						printf("! ");
				k++;
				res[(i) * (horizontal_ + 1) + j] += EPosition::RIGHT;
			}

			if (cell_[i][j].west_ == Cell::WALL)
				res[(i + 1) * (horizontal_ + 1) + j] += EPosition::DOWN;
		}

		res[(i + 1) * (horizontal_ + 1) + horizontal_] += EPosition::DOWN;
	}

	for (int j = 0; j < horizontal_; j++)
		res[(vertical_) * (horizontal_ + 1) + j] += EPosition::RIGHT;

	return res;
}