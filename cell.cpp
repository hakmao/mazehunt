#include "cell.h"

Direction opposite_direction(Direction d)
{
    switch (d)
    {
    case Direction::East:
        return Direction::West;
        break;
    case Direction::South:
        return Direction::North;
        break;
    case Direction::West:
        return Direction::East;
        break;
    case Direction::North:
        return Direction::South;
        break;
    }
}

Cell::Cell(int r, int c) : row{r}, col{c} {}
int Cell::get_row()
{
    return row;
}
int Cell::get_col()
{
    return col;
}
void Cell::create_link_to(Direction d)
{
    if (links.count(d) < 1)
    {
        links.insert(d);
        Cell *c = get_neighbour(d);
        c->create_link_to(opposite_direction(d));
    }
}
void Cell::unlink_from(Direction d)
{
    if (links.count(d) > 0)
    {
        links.erase(d);
        Cell *c = get_neighbour(d);
        c->unlink_from(opposite_direction(d));
    }
}
bool Cell::is_linked_to(Direction d)
{
    return (links.count(d) > 0);
}
std::set<Direction> Cell::all_links()
{
    return links;
}
void Cell::set_neighbour(Direction d, Cell *cell)
{
    neighbours[d] = cell;
}
Cell *Cell::get_neighbour(Direction d)
{
    return neighbours[d];
}
std::map<Direction, Cell *> Cell::all_neighbours()
{
    return neighbours;
}
