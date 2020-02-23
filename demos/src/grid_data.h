//
// Created by Johannes Flieger on 19/01/2020.
//

#ifndef GRID_DATA_H
#define GRID_DATA_H

#include "grid.h"

namespace grid_data
{
    // Sample grids
    int const sample_grid_1_rows = 5;
    int const sample_grid_1_cols = 6;
    int const sample_grid_1_size = 5 * 6;
    vector<vector<State>> const sample_grid_1 = {
            { State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle },
            { State::Obstacle, State::Player,   State::Obstacle, State::Empty,    State::Zombie,   State::Obstacle },
            { State::Obstacle, State::Empty,    State::Obstacle, State::Empty,    State::Obstacle, State::Obstacle },
            { State::Obstacle, State::Empty,    State::Empty,    State::Food,     State::Empty,    State::Obstacle },
            { State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle }};

    vector<vector<State>> const sample_grid_2 = {
            { State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle },
            { State::Obstacle, State::Food,     State::Obstacle, State::Empty,    State::Zombie,   State::Obstacle },
            { State::Obstacle, State::Empty,    State::Obstacle, State::Empty,    State::Empty,    State::Obstacle },
            { State::Obstacle, State::Player,   State::Empty,    State::Empty,    State::Empty,    State::Obstacle },
            { State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle }};

    // Test file name
    std::string const testfile( "test.grid");
}
#endif //GRID_DATA_H
