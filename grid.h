#ifndef GRID_H
#define GRID_H

#include <vector>

using std::string;
using std::vector;

struct Cell
{
	int x;
	int y;

	Cell(int a, int b) : x{ a }, y{ b } {}; // for use with emplace_back()
};

enum class State
{
	Empty = 0,
	Obstacle,
	Food,
	Player,
	Zombie,
	Visited
};

using GridRow = vector<State>;
using GridLayout = vector <vector<State>>;
//using Path = deque<Cell>;

class Grid
{

public:
	// Constructors
	Grid();

	Grid(GridLayout);

	Grid(string path);

	// methods
	string to_str() const;

	bool from_file(string path);
	bool to_file(string path);
	bool is_move_okay(Cell c) const;
	bool is_on_grid(Cell c) const;

	GridLayout global_state() const;
	State cell_state(Cell const& c);

	int size() const;
	int rows() const;
	int cols() const;

	// friends
	friend bool operator==(Grid const& g1, Grid const& g2);

	friend bool operator!=(Grid const& g1, Grid const& g2);

	friend std::ostream& operator<<(std::ostream& out, Grid const& g);

private:
	// data
	GridLayout state{};

	// methods
	GridLayout read_file(string file);

	GridRow parse_line(string line);

};

#endif
