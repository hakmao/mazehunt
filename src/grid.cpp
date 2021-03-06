#include <fstream>
#include <iostream>
#include <sstream>

#include "grid.h"


/******/
bool Cell::operator==(Cell const& other)
{
    return (this->x == other.x && this->y == other.y);
}

bool Cell::is_neighbour(Cell const& other)
{
    int x_delta = std::abs(this->x - other.x);
    int y_delta = std::abs(this->y - other.y);

    bool row_neighbours = x_delta == 0 && y_delta < 2;
    bool col_neighbours = y_delta == 0 && x_delta < 2;
    if (row_neighbours || col_neighbours)
        return true;
    else
        return false;
}

/******/
bool operator==(const Grid& g1, const Grid& g2)
{
    return (g1.state == g2.state);
}

bool operator!=(const Grid& g1, const Grid& g2)
{
    return !(g1 == g2);
}

// Public
Grid::Grid()
{}

Grid::Grid(vector <vector<State>> g)
{
    state = g;
}

Grid::Grid(string path)
{
    from_file(path);
}

int Grid::size() const
{
    return rows() * cols();
}

int Grid::rows() const
{
    return state.size();
}

int Grid::cols() const
{
    return state[0].size();
}

GridLayout Grid::global_state() const
{
    return state;
}

State Grid::cell_state(Cell const& c)
{
    return state[c.x][c.y];
}

bool Grid::from_file(string path)
{
    if (!state.empty())
        state.clear();
    state = read_file(path);
    if (state.empty())
        return false;
    else
        return true;
}

bool Grid::to_file(string path)
{
    if (state.empty())
    {
        std::cerr << "Grid is empty: nothing to write." << std::endl;
        return false;
    }
    else
    {
        std::ofstream grid_file(path);
        if (grid_file)
        {
            for (auto& row : state)
            {
                for (auto it = row.begin(); it != row.end(); it++)
                {
                    grid_file << static_cast<int>(*it) << ",";
                }
                grid_file << "\n";
            }
            return true;
        }
        else
        {
            std::cerr << "Could not open file for reading." << std::endl;
            return false;
        }
    }
}

string Grid::to_str() const
{
    if (state.empty())
    {
        std::cerr << "Grid is empty: nothing to write." << std::endl;
        return "";
    }
    else
    {
        std::ostringstream oss;
        for (auto& row : state)
        {
            for (auto it = row.begin(); it != row.end(); it++)
            {
                oss << static_cast<int>(*it) << ",";
            }
            oss << "\n";
        }
        return oss.str();
    }
}

std::ostream& operator<<(std::ostream& out, Grid const& g)
{
    return (out << g.to_str());
}

// Private
vector <State> Grid::parse_line(string line)
{
    std::istringstream str_line(line);
    int n;
    char c;
    vector <State> row;
    while (str_line >> n >> c && c == ',')
    {
        row.push_back(static_cast<State>(n));
    }
    return row;
}

vector <vector<State>> Grid::read_file(string path)
{
    vector <vector<State>> new_grid{};
    std::ifstream grid_file(path);
    if (grid_file)
    {
        string line;
        while (getline(grid_file, line))
        {
            vector <State> row = parse_line(line);
            new_grid.push_back(row);
        }
    }
    else
    {
        std::cerr << "Could not open file for reading." << std::endl;
    }
    return new_grid;
}

bool Grid::is_on_grid(Cell c) const
{
    bool on_grid_x = (c.x >= 0 && c.x < state[0].size());
    bool on_grid_y = (c.y >= 0 && c.y < state.size());
    return (on_grid_x && on_grid_y);
}

bool Grid::is_move_okay(Cell c) const
{
    if (!is_on_grid(c))
    {
        return false;
    }
    State cellState = state[c.x][c.y];
    switch (cellState)
    {
        case State::Obstacle: return false;
            break;
        case State::Zombie:
        case State::Empty:
        case State::Food:
        case State::Player:
        default: return true;
    }
}

//End of file
