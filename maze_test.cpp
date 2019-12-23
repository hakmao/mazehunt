#include <iostream>

#include "defs.h"
#include "maze.h"

int main()
{
    Maze maze(GRID_ROWS, GRID_COLS);
    std::cout << "\n===== ASCII Drawing =====\n" << std::endl;
	std::cout << maze << std::endl;
    std::cout << "\n===== Grid Representation =====\n" << std::endl;
    std::cout << maze.to_grid() << std::endl;
   
    return 0;
}
