#include <fstream>
#include <iostream>
#include <sstream>

#include "grid.h"

bool operator== (const Grid& g1, const Grid& g2)
{
    return (g1.gridstate == g2.gridstate);
}

bool operator!= (const Grid& g1, const Grid& g2)
{
    return !(g1 == g2);
}

// Public
Grid::Grid(){}

Grid::Grid(vector<vector<State>> g)
{
    gridstate = g;
}

Grid::Grid(string path)
{
    from_file(path);
}

int Grid::size()
{
    return rows() * cols();
}

int Grid::rows()
{
    return gridstate.size();
}

int Grid::cols()
{
    return gridstate[0].size();
}

vector<vector<State>> Grid::state()
{
    return gridstate;
}

void Grid::from_file(string path)
{
    if (!gridstate.empty())
        gridstate.clear();
    gridstate = read_file(path);
}

void Grid::to_file(string path)
{
    if (gridstate.empty())
        std::cerr << "Grid is empty: nothing to write." << std::endl;
    else
    {
        std::ofstream grid_file(path);
        if (grid_file)
        {
            for (auto &row : gridstate)
            {
                for (auto it = row.begin(); it != row.end(); it++)
                {
                    grid_file << static_cast<int>(*it) << ",";
                }
                grid_file << "\n";
            }
        }
        else
        {
            std::cerr << "Could not open file for reading." << std::endl;
        }
    }
}

string Grid::to_str()
{
    if (gridstate.empty())
    {
        std::cerr << "Grid is empty: nothing to write." << std::endl;
        return "";
    }
    else
    {
        std::ostringstream oss;
        for (auto& row : gridstate)
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

std::ostream &operator<<(std::ostream &out, Grid &g)
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
