#ifndef NODE_H
#define NODE_H

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

class Node
{
public:
    Node(int r, int c);
    int get_row();
    int get_col();
    bool is_linked_to(Direction d);
    void create_link_to(Direction d);
    void unlink_from(Direction d);
    std::set<Direction> all_links();
    void set_neighbour(Direction d, Node *n);
    Node *get_neighbour(Direction d);
    std::map<Direction, Node *> all_neighbours();

private:
    int row{0};
    int col{0};
    std::map<Direction, Node *> neighbours{};
    // std::set<Node *> links{};
    std::set<Direction> links{};
};

#endif
