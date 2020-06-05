// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

enum class EDirection;

struct Cell
{
    enum
    {
        NO_WALL = 0,
        WALL = 1,
        RANDOM_NUMBER = 56
    };
    int north_, west_, east_, south_;
    int set_ = 0;

    Cell() : north_(NO_WALL), west_(NO_WALL), east_(NO_WALL), south_(NO_WALL) {}

    int delete_wall(EDirection dir);
    bool check_wall(EDirection dir);
};


struct Cell_Improved
{
    // Wall_position[0] -> up, Wall_position[1] -> Left
    int Wall_position[2] = { 0, 0 };

    // [0] -> up left, [1] -> up right, [2] -> down left, [3] -> down right
    int CornerDecoration_position[4] = {0, 0, 0, 0 };

    // Up Left corner (=0 -> none); (=1 -> box); (=2 -> fancy_1) (=3 -> fancy_2 - diff rotation) (=4 -> plug)
    enum class EFaceDecorationType
    {
        None = 0,
        Box,
        Bend_UpRight,
        Bend_UpLeft,
        Bend_DownRight,
        Bend_DownLeft,
        Plug_Up,
        Plug_Down,
        Plug_Right,
        Plug_Left
    };
    EFaceDecorationType FaceDecoration_position = EFaceDecorationType::None;
};

struct Maze
{
private:
    Cell** cell_;
    int* intermediate_array;
    int vertical_, horizontal_;

    int change_array_before_start(Cell** array, int number, int range);
    int last_line_processing(Cell* array, int range);
    Cell_Improved** convert();
    void Construct() noexcept;

    Cell_Improved ** placement;

public:
    Maze(int vert, int horiz);
    ~Maze();
    enum EPosition
    {
        NOTHING = 0,
        RIGHT = 1,
        DOWN = 2,
        BOTH = 3
    };
    Cell_Improved const & At (int i, int j) const noexcept;
};