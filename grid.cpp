#include <fstream>
#include <iostream>
#include <sstream>

#include "grid.h"

bool operator== (const Grid& g1, const Grid& g2)
{
    return (g1.state == g2.state);
}

bool operator!= (const Grid& g1, const Grid& g2)
{
    return !(g1 == g2);
}

// Public
Grid::Grid(){}

Grid::Grid(vector<vector<State>> g)
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

GridLayout Grid::get_state() const
{
    return state;
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
            for (auto &row : state)
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

std::ostream &operator<<(std::ostream &out, Grid const &g)
{
    return (out << g.to_str());
}

// Private
vector<State> Grid::parse_line(string line)
{
    std::istringstream str_line(line);
    int n;
    char c;
    vector<State> row;
    while (str_line >> n >> c && c == ',')
    {
        row.push_back(static_cast<State>(n));
    }
    return row;
}

vector<vector<State>> Grid::read_file(string path)
{
    vector<vector<State>> new_grid{};
    std::ifstream grid_file(path);
    if (grid_file)
    {
        string line;
        while (getline(grid_file, line))
        {
            vector<State> row = parse_line(line);
            new_grid.push_back(row);
        }
    }
    else
    {
        std::cerr << "Could not open file for reading." << std::endl;
    }
    return new_grid;
}

//End of file
