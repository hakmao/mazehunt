#ifndef MAZE_H
#define MAZE_H

// #include <iostream>
// #include <functional>
#include <vector>
#include "node.h"

class Maze
{
public:
    Maze(int nrows, int ncols);               // constructs a maze with the given dimensions
    int size();                               // returns the total number of cells in the grid
    int count_rows();                         // returns the number of rows in the grid
    int count_cols();                         // returns the number of columns in the grid
    bool is_valid_location(int row, int col);
    Node *node(int row, int col); // returns the node at the specified position
    Node  *random_node();          // selects a random node in the grid
    void for_each_node(std::function<void(Node &)> linker); // apply function to each cell in the grid
    void generate();
    std::string to_str();
    friend std::ostream &operator<<(std::ostream &out, Maze &g);

private:
    // data
    std::vector<Node> nodes;
    // methods
    void setup();
    void configure();
    void link(Node& node);
    int num_rows{1};
    int num_cols{1};
    int node_index(int r, int c);
};

#endif
