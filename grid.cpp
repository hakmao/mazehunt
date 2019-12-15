// #include <string>
// #include <algorithm>
#include <sstream>
#include "utils.h"
#include "grid.h"

template <typename T>
T *getPointer(T &t) { return &t; }

Grid::Grid(int nrows, int ncols) : num_rows{nrows}, num_cols{ncols}
{
    assert(1 <= nrows && 1 <= ncols);
    cells.reserve(nrows * ncols);
    setup();
    configure();
    generate();
}

bool Grid::is_valid_location(int row, int col)
{
    if (0 <= row && row < num_rows)
        return (0 <= col && col < num_cols);
    else
        return false;
}
int Grid::cell_index(int r, int c)
{
    return (r * num_cols) + c;
}
Cell *Grid::cell(int r, int c)
{
    if (is_valid_location(r, c))
        return &cells[cell_index(r, c)];
    else
        return nullptr;
}

void Grid::setup()
{
    for (int r{0}; r < num_rows; ++r)
    {
        for (int c{0}; c < num_cols; ++c)
        {
            cells.emplace_back(r, c);
        }
    }
}

void Grid::configure()
{
    for (auto &c : cells)
    {
        int row = c.get_row();
        int col = c.get_col();
        c.set_neighbour(Direction::East, cell(row, col + 1));
        c.set_neighbour(Direction::South, cell(row + 1, col));
        c.set_neighbour(Direction::West, cell(row, col - 1));
        c.set_neighbour(Direction::North, cell(row - 1, col));
    }
}
void Grid::generate()
{
    for (auto &c: cells)
        link(c);
}
void Grid::link(Cell& cell)
{
   std::vector<Direction> ns(2);
    // check if cell has neighbours to the east and north
    Cell *east = cell.get_neighbour(Direction::East);
    Cell *north = cell.get_neighbour(Direction::North);
    if (east == nullptr && north == nullptr)
        return;
    else if (east == nullptr && north != nullptr)
        cell.create_link_to(Direction::North);
    else if (east != nullptr && north == nullptr)
        cell.create_link_to(Direction::East);
    else // Cell has both eastern and northern neighbours
    {
        ns = {Direction::East, Direction::North};
        cell.create_link_to(ns[Utils::random_index(2)]);
    }
}

Cell *Grid::random_cell()
{
    int index = Utils::random_int_in_range(0, size() - 1);

    return &cells[index];
}

int Grid::size()
{
    return (num_rows * num_cols);
}
int Grid::count_rows()
{
    return num_rows;
}
int Grid::count_cols()
{
    return num_cols;
}

void Grid::for_each_cell(std::function<void(Cell &)> linker)
{
    for_each(cells.begin(), cells.end(), linker);
}

std::string Grid::to_str()
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
    std::string cell_gap("   ");
    // proceed by rows
    for (int r{0}; r < num_rows; r++)
    {
        std::string row_top(v_separator);
        std::string row_bottom(corner);
        for (int c{0}; c < num_cols; c++)
        {
            std::string east_border = cell(r, c)->is_linked_to(Direction::East) ? " " : v_separator;
            row_top += cell_gap;
            row_top += east_border;
            std::string south_border = cell(r, c)->is_linked_to(Direction::South) ? cell_gap : h_separator;
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
std::ostream &operator<<(std::ostream &out, Grid &g)
{
    return (out << g.to_str());
}
