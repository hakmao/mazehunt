#include <sstream>
#include "utils.h"
#include "maze.h"

template <typename T>
T *getPointer(T &t) { return &t; }

Maze::Maze(int nrows, int ncols) : num_rows{nrows}, num_cols{ncols}
{
    assert(1 <= nrows && 1 <= ncols);
    nodes.reserve(nrows * ncols);
    setup();
    configure();
    generate();
}

bool Maze::is_valid_location(int row, int col)
{
    if (0 <= row && row < num_rows)
        return (0 <= col && col < num_cols);
    else
        return false;
}
int Maze::node_index(int r, int c)
{
    return (r * num_cols) + c;
}
Node *Maze::node(int r, int c)
{
    if (is_valid_location(r, c))
        return &nodes[node_index(r, c)];
    else
        return nullptr;
}

void Maze::setup()
{
    for (int r{0}; r < num_rows; ++r)
    {
        for (int c{0}; c < num_cols; ++c)
        {
            nodes.emplace_back(r, c);
        }
    }
}

void Maze::configure()
{
    for (auto &c : nodes)
    {
        int row = c.get_row();
        int col = c.get_col();
        c.set_neighbour(Direction::East, node(row, col + 1));
        c.set_neighbour(Direction::South, node(row + 1, col));
        c.set_neighbour(Direction::West, node(row, col - 1));
        c.set_neighbour(Direction::North, node(row - 1, col));
    }
}
void Maze::generate()
{
    for (auto &c: nodes)
        link(c);
}
void Maze::link(Node& node)
{
   std::vector<Direction> ns(2);
    // check if node has neighbours to the east and north
    Node *east = node.get_neighbour(Direction::East);
    Node *north = node.get_neighbour(Direction::North);
    if (east == nullptr && north == nullptr)
        return;
    else if (east == nullptr && north != nullptr)
        node.create_link_to(Direction::North);
    else if (east != nullptr && north == nullptr)
        node.create_link_to(Direction::East);
    else // Node has both eastern and northern neighbours
    {
        ns = {Direction::East, Direction::North};
        node.create_link_to(ns[Utils::random_index(2)]);
    }
}

//Node *Maze::random_node()
//{
//    int index = Utils::random_int_in_range(0, size() - 1);
//
//    return &nodes[index];
//}

int Maze::size()
{
    return (num_rows * num_cols);
}
int Maze::count_rows()
{
    return num_rows;
}
int Maze::count_cols()
{
    return num_cols;
}

void Maze::for_each_node(std::function<void(Node &)> linker)
{
    for_each(nodes.begin(), nodes.end(), linker);
}

std::ostream &operator<<(std::ostream &out, Maze &m)
{
    return (out << m.to_str());
}

std::string Maze::to_str()
{
    std::string h_border("+");
    for (int c{0}; c < num_cols; c++)
        h_border += "---+";
    h_border += "\n";
    std::string output(h_border);
    // Define ASCII elements
    std::string v_separator("|");
    std::string corner("+");
    std::string h_separator("---");
    std::string node_gap("   ");
    // proceed by rows
    for (int r{0}; r < num_rows; r++)
    {
        std::string row_top(v_separator);
        std::string row_bottom(corner);
        for (int c{0}; c < num_cols; c++)
        {
            std::string east_border = node(r, c)->is_linked_to(Direction::East) ? " " : v_separator;
            row_top += node_gap;
            row_top += east_border;
            std::string south_border = node(r, c)->is_linked_to(Direction::South) ? node_gap : h_separator;
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
    for (int c{0}; c < num_cols; c++)
        h_border += "1,1,1,1,";
    h_border += "\n";
    std::string output(h_border);
    // Define ASCII elements
    std::string v_separator("1,");
    std::string corner("1,");
    std::string h_separator("1,1,1,");
    std::string node_gap("0,0,0,");
    // proceed by rows
    for (int r{0}; r < num_rows; r++)
    {
        std::string row_top(v_separator);
        std::string row_bottom(corner);
        for (int c{0}; c < num_cols; c++)
        {
            std::string east_border = node(r, c)->is_linked_to(Direction::East) ? "0," : v_separator;
            row_top += node_gap;
            row_top += east_border;
            std::string south_border = node(r, c)->is_linked_to(Direction::South) ? node_gap : h_separator;
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