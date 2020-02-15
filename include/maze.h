#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <memory>
#include <vector>
#include <set>
#include <map>
#include <utility>
//#include "node.h"

using std::vector;
using std::set;
using std::map;
using std::shared_ptr;
using std::string;
using std::pair;

enum class Direction
{
    East,
    South,
    West,
    North
};

struct Node;
using RowCol = std::pair<int, int>;
using NodePtr = std::shared_ptr<Node>;

struct Node
{
    // data
    int row;
    int col;
    map <Direction, NodePtr> neighbours{};
    set <Direction> links{};

    // functions
    Node(int r, int c);

    RowCol neighbour_at(Direction d);

    static Direction opposite(Direction d);

    void create_link(Direction d);

    void remove_link(Direction d);

    void clear_links();
};

class Maze
{
public:
    // methods
    Maze(int nr, int nc);               // constructs a maze with the given dimensions
    int size();                               // returns the total number of nodes
    int get_num_rows();                         // returns the number of rows
    int get_num_cols();                         // returns the number of columns
    void regenerate();
    string to_str();
    string to_grid();
    friend std::ostream& operator<<(std::ostream& out, Maze& m);

private:
    // data
    int num_rows{ 0 };
    int num_cols{ 0 };
    std::vector <NodePtr> nodes{};

    // methods
    void setup();

    void configure();

    void generate();

    bool is_valid_location(int row, int col);

    int get_node_index(int r, int c);

    NodePtr get_node_ptr(RowCol rc); // returns pointer to the node at the specified position

    void link_neighbours(NodePtr n);

    void reset_links();
};

#endif
