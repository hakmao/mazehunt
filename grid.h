#ifndef GRID_H
#define GRID_H

// #include <iostream>
// #include <functional>
#include <vector>
#include "cell.h"

class Grid
{
public:
    Grid(int nrows, int ncols);               // constructs a grid with the given dimensions
    int size();                               // returns the total number of cells in the grid
    int count_rows();                         // returns the number of rows in the grid
    int count_cols();                         // returns the number of columns in the grid
    bool is_valid_location(int row, int col);
    Cell *cell(int row, int col); // returns the cell at the specified position
    Cell *random_cell();          // selects a random cell in the grid
    // void for_each_row(std::function<void(std::vector<Cell *>)> linker); // apply function to each row of the grid
    void for_each_cell(std::function<void(Cell &)> linker); // apply function to each cell in the grid
    void generate();
    std::string to_str();
    friend std::ostream &operator<<(std::ostream &out, Grid &g);

private:
    // data
    std::vector<Cell> cells;
    // methods
    void setup();
    void configure();
    void link(Cell& cell);
    int num_rows{1};
    int num_cols{1};
    int cell_index(int r, int c);
};

#endif
