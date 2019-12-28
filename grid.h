#ifndef GRID_H
#define GRID_H

#include <vector>

using std::string;
using std::vector;

struct Cell
{
    int x;
    int y;
    Cell(int a, int b): x{a}, y{b}{}; // for emplace_back()
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
private:
    GridLayout state{};

    GridRow parse_line(string line);

    GridLayout read_file(string file);

public:
    Grid();

    Grid(GridLayout);

    Grid(string path);

    string to_str();

    void from_file(string path);

    void to_file(string path);

    GridLayout get_state();

    int size();

    int rows();

    int cols();

    friend bool operator==(const Grid& g1, const Grid& g2);

    friend bool operator!=(const Grid& g1, const Grid& g2);

    friend std::ostream& operator<<(std::ostream& out, Grid& g);

};

#endif
