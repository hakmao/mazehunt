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

TEST_CASE("Initialise Node ", "[node][maze]")
{
    Node node(5, 5); // Origin
    Node nodeE(5, 6); // East
    Node nodeS(6, 5); // South
    Node nodeW(5, 4); // West
    Node nodeN(4, 5); // North

    SECTION("Node data is correct at initialisation")
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
    SECTION("Check neighbour coordinates")
    {
        auto [rE,cE] = node.neighbour_at( Direction::East);
        auto [rS,cS] = node.neighbour_at( Direction::South);
        auto [rW,cW] = node.neighbour_at( Direction::West);
        auto [rN,cN] = node.neighbour_at( Direction::North);

        CHECK(rN == 4);
        CHECK(cN == 5);
        CHECK(rS == 6);
        CHECK(cS == 5);
        CHECK(rE == 5);
        CHECK(cE == 6);
        CHECK(rW == 5);
        CHECK(cW == 4);
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


