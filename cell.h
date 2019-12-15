#ifndef CELL_H
#define CELL_H

#include <map>
#include <set>

enum class Direction
{
    East,
    South,
    West,
    North
};
Direction opposite_direction(Direction d);

class Cell
{
public:
    Cell(int r, int c);
    int get_row();
    int get_col();
    bool is_linked_to(Direction d);
    void create_link_to(Direction d);
    void unlink_from(Direction d);
    std::set<Direction> all_links();
    void set_neighbour(Direction d, Cell *cell);
    Cell *get_neighbour(Direction d);
    std::map<Direction, Cell *> all_neighbours();

private:
    int row{0};
    int col{0};
    std::map<Direction, Cell *> neighbours{};
    // std::set<Cell *> links{};
    std::set<Direction> links{};
};

#endif
