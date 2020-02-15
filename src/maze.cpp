#include <iostream>
#include <sstream>
//#include <pair>
#include "utils.h"
#include "maze.h"

/*** Node ***/
Node::Node(int r, int c) : row{ r }, col{ c }
{}

pair<int, int> Node::neighbour_at(Direction d)
{
    int r = -1;
    int c = -1;
    switch (d)
    {
        case Direction::East:r = row;
            c = col + 1;
            break;
        case Direction::South:r = row + 1;
            c = col;
            break;
        case Direction::West:r = row;
            c = col - 1;
            break;
        case Direction::North:r = row - 1;
            c = col;
            break;
    }
    return std::make_pair(r, c);
}

Direction Node::opposite(Direction d)
{
    Direction opp;
    switch (d)
    {
        case Direction::East:opp = Direction::West;
            break;
        case Direction::South:opp = Direction::North;
            break;
        case Direction::West:opp = Direction::East;
            break;
        case Direction::North:opp = Direction::South;
            break;
    }
    return opp;
}

// Link a node to its neighbour located in direction d
void Node::create_link(Direction d)
{
    auto neighbourNode = neighbours[d];
    if (neighbourNode != nullptr)
    {
        links.insert(d);
        neighbourNode->links.insert(Node::opposite(d));
    }
}

void Node::remove_link(Direction d)
{
    auto neighbour = neighbours[d];
    if (neighbour != nullptr)
    {
        links.erase(d);
        neighbour->links.erase(Node::opposite(d));
    }
}

void Node::clear_links()
{
    this->links.clear();
}

/*** Maze ***/

Maze::Maze(int nrows, int ncols) : num_rows{ nrows }, num_cols{ ncols }
{
    assert(1 <= nrows && 1 <= ncols);
    nodes.reserve(nrows * ncols);
    setup();
    configure();
    generate();
}

void Maze::setup()
{
    for (int r{ 0 }; r < num_rows; ++r)
    {
        for (int c{ 0 }; c < num_cols; ++c)
        {
            nodes.push_back(std::make_shared<Node>(r, c));
        }
    }
}

// Return size of the maze grid
int Maze::size()
{
    return (num_rows * num_cols);
}

// Return number of columns in the maze grid
int Maze::get_num_rows()
{
    return num_rows;
}

// Return number of columns in the maze grid
int Maze::get_num_cols()
{
    return num_cols;
}

// Check whether the position corresponding to <row, col> is on the maze grid
bool Maze::is_valid_location(int row, int col)
{
    if (0 <= row && row < num_rows)
        return (0 <= col && col < num_cols);
    else
        return false;
}

// Get the index corresponding to the maze position <row,col> in the vector of nodes
int Maze::get_node_index(int row, int col)
{
    return (row * num_cols) + col;
}

// Returns a pointer to the node indicated by pair <row, col>
std::shared_ptr <Node> Maze::get_node_ptr(RowCol rc)
{
    int row = rc.first;
    int col = rc.second;
    if (!is_valid_location(row, col))
        return nullptr;
    else
    {
        int idx = get_node_index(row, col);
        return nodes[idx];
    }
}

// For each node in the maze, assign a pointer to its neighbours
void Maze::configure()
{
    for (auto& n : nodes)
    {
        n->neighbours[Direction::East] = get_node_ptr(n->neighbour_at(Direction::East));
        n->neighbours[Direction::South] = get_node_ptr(n->neighbour_at(Direction::South));
        n->neighbours[Direction::West] = get_node_ptr(n->neighbour_at(Direction::West));
        n->neighbours[Direction::North] = get_node_ptr(n->neighbour_at(Direction::North));
    }
}

// Clear the set of links for each node, while preserving the information on its neighbours
void Maze::reset_links()
{
    for (auto n: nodes)
    {
        n->clear_links();
    }
}

// Clear existing maze and generate a new one
void Maze::regenerate(){
    reset_links();
    generate();
}

// Generate a maze by creating links between neighbouring nodes
void Maze::generate()
{
    for (auto& n: nodes)
        link_neighbours(n);
}

void Maze::link_neighbours(std::shared_ptr <Node> node){
    // check if node has neighbours to the east and north
    auto east = node->neighbours[Direction::East];
    auto north = node->neighbours[Direction::North];
    if (east == nullptr && north == nullptr)
        return;
    else if (east == nullptr && north != nullptr)
        node->create_link(Direction::North);
    else if (east != nullptr && north == nullptr)
        node->create_link(Direction::East);
    else // Node has both eastern and northern neighbours
    {
        std::vector <Direction> ns = { Direction::East, Direction::North };
        node->create_link(ns[Utils::random_index(2)]);
    }
}

std::ostream& operator<<(std::ostream& out, Maze& m)
{
    return (out << m.to_str());
}

std::string Maze::to_str()
{
    std::string h_border("+");
    for (int c{ 0 }; c < num_cols; c++)
        h_border += "---+";
    h_border += "\n";
    std::string output(h_border);
    // Define ASCII elements
    std::string v_separator("|");
    std::string corner("+");
    std::string h_separator("---");
    std::string node_gap("   ");
    // proceed by rows
    for (int r{ 0 }; r < num_rows; r++)
    {
        std::string row_top(v_separator);
        std::string row_bottom(corner);
        for (int c{ 0 }; c < num_cols; c++)
        {
            auto np = get_node_ptr(std::make_pair(r, c));
            bool linked_east = (np->links.count(Direction::East) > 0);
            bool linked_south = (np->links.count(Direction::South) > 0);
            std::string east_border = linked_east ? " " : v_separator;
            row_top += node_gap;
            row_top += east_border;
            std::string south_border = linked_south ? node_gap : h_separator;
            row_bottom += south_border;
            row_bottom += corner;
        }
        output += row_top;
        output += "\n";
        output += row_bottom;
        output += "\n";
    }
    return output;
}

std::string Maze::to_grid()
{
    std::string h_border("1,");
    for (int c{ 0 }; c < num_cols; c++)
        h_border += "1,1,1,1,";
    h_border += "\n";
    std::string output(h_border);
    // Define ASCII elements
    std::string v_separator("1,");
    std::string corner("1,");
    std::string h_separator("1,1,1,");
    std::string node_gap("0,0,0,");
    // proceed by rows
    for (int r{ 0 }; r < num_rows; r++)
    {
        std::string row_top(v_separator);
        std::string row_bottom(corner);
        for (int c{ 0 }; c < num_cols; c++)
        {
            auto np = get_node_ptr(std::pair(r, c));
            bool linked_east = (np->links.count(Direction::East) > 0);
            bool linked_south = (np->links.count(Direction::South) > 0);
            std::string east_border = linked_east ? "0," : v_separator;
            row_top += node_gap;
            row_top += east_border;
            std::string south_border = linked_south ? node_gap : h_separator;
            row_bottom += south_border;
            row_bottom += corner;
        }
        output += row_top;
        output += "\n";
        output += row_bottom;
        output += "\n";
    }

    return output;
}

//End of file