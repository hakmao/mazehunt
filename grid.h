#ifndef GRID_H
#define GRID_H

#include <vector>

using std::string;
using std::vector;

enum class State
{
    Empty = 0,
    Obstacle,
    Food,
    Player,
    Zombie
};

class Grid
{
  public:
    Grid();
    Grid(vector<vector<State>>);
    Grid(string path);
    string to_str();
    void from_file(string path);
    void to_file(string path);
    vector<vector<State>> state();
    int size();
    int rows();
    int cols();
    friend bool operator== (const Grid& g1, const Grid& g2);
    friend bool operator!= (const Grid& g1, const Grid& g2);
    friend std::ostream &operator<<(std::ostream &out, Grid &g);

  private:
    vector<vector<State>> gridstate{};
    vector<State> parse_line(string line);
    vector<vector<State>> read_file(string file);
};

#endif
