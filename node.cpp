#include "node.h"

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

Node::Node(int r, int c) : row{r}, col{c} {}
int Node::get_row()
{
    return row;
}
int Node::get_col()
{
    return col;
}
void Node::create_link_to(Direction d)
{
    if (links.count(d) < 1)
    {
        links.insert(d);
        Node *n = get_neighbour(d);
        n->create_link_to(opposite_direction(d));
    }
}
void Node::unlink_from(Direction d)
{
    if (links.count(d) > 0)
    {
        links.erase(d);
        Node *n = get_neighbour(d);
        n->unlink_from(opposite_direction(d));
    }
}
bool Node::is_linked_to(Direction d)
{
    return (links.count(d) > 0);
}
std::set<Direction> Node::all_links()
{
    return links;
}
void Node::set_neighbour(Direction d, Node *node)
{
    neighbours[d] = node;
}
Node *Node::get_neighbour(Direction d)
{
    return neighbours[d];
}
std::map<Direction, Node *> Node::all_neighbours()
{
    return neighbours;
}
