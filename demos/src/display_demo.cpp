//
// Created by Johannes Flieger on 04/03/2020.
//

#include "defs.h"
#include "maze.h"
#include "display.h"

int main()
{
    int win_height = SCREEN_LINES;
    int win_width = SCREEN_COLS;
    Maze maze(GRID_ROWS, GRID_COLS);
    NCursesDisplay display{win_height, win_width};

    display.start_grid(maze.to_str());

    return 0;
}