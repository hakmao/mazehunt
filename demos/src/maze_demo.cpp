#include <iostream>

#include "defs.h"
#include "maze.h"

void display_maze(Maze m)
{
    std::cout << "\n===== ASCII Drawing =====\n" << std::endl;
    std::cout << m << std::endl;
    std::cout << "\n===== Grid Representation =====\n" << std::endl;
    std::cout << m.to_grid() << std::endl;
}

int main()
{
    Maze maze(GRID_ROWS, GRID_COLS);
    display_maze(maze);
    // Generate new maze
    maze.regenerate();
    display_maze(maze);

    return 0;
}
