//
// Created by Johannes Flieger on 02/01/2020.
//
#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#endif

//#include <memory>
#include "maze.h"

TEST_CASE("Node static functions")
{
    SECTION("Get opposite direction")
    {
        CHECK(Direction::South == Node::opposite(Direction::North));
        CHECK(Direction::North == Node::opposite(Direction::South));
    }
}

TEST_CASE("Node initialisation", "[node][maze]")
{
    Node node(5, 5);
    Node nodeN(4, 5);

    SECTION("Initialise data")
    {
        CHECK(node.row == 5);
        CHECK(node.col == 5);
        CHECK(nodeN.row == 4);
        CHECK(nodeN.col == 5);
        CHECK(node.links.empty());
        CHECK(node.neighbours.empty());
        CHECK(nodeN.links.empty());
        CHECK(nodeN.neighbours.empty());
    }
    SECTION("Get neighbour coordinates")
    {
        auto [r1,c1] = node.neighbour_at( Direction::North);
        auto [r2,c2] = nodeN.neighbour_at( Direction::South);

        CHECK(r1 == 4);
        CHECK(c1 == 5);
        CHECK(r2 == 5);
        CHECK(c2 == 5);
    }
}

TEST_CASE("Initialise maze", "[maze]")
{
    Maze maze(4,4);

    SECTION("Check maze size")
    {
        CHECK(maze.get_num_rows() == 4);
        CHECK(maze.get_num_cols() == 4);
        CHECK(maze.size() == 16);
    }

}


