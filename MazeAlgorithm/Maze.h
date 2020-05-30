enum class EDirection;

struct Cell
{
    enum
    {
        WALL,
        NO_WALL,
        RANDOM_NUMBER = 56
    };
	int north_, west_, east_, south_;
	int set_;

    Cell() : north_(NO_WALL), west_(NO_WALL), east_(NO_WALL), south_(NO_WALL) {}

	int delete_wall(EDirection dir);
	bool check_wall(EDirection dir);	
};

struct Maze
{
private:
	Cell** cell_;
    int * intermediate_array;
	int vertical_, horizontal_;

    int change_array_before_start(Cell ** array, int number, int range);
	int last_line_processing(Cell * array, int range);
    int * convert();
    void Construct() noexcept;

    int * placement;

public:
	Maze(int vert, int horiz);
	~Maze();

	int print_maze();

    enum EPosition
    {
        NOTHING = 0,
        RIGHT = 1,
        DOWN = 2,
        BOTH = 3
    };
};