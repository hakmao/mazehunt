// #include <iostream>
// #include <string>
// #include <ncurses.h>
// #include "defs.h"
// #include "grid.h"
#include "game.h"

int main(int argc, char *argv[])
{
    // std::cout << "Creating maze...\n";
    // Grid maze(GRID_ROWS, GRID_COLS);
    // NCursesDisplay ncdisplay(TEXT_LINES, TEXT_COLS);
    // std::string maze_str = maze.to_str();
    // ncdisplay.display_grid(maze_str);
    // ncdisplay.display_player(1,1);
    Game game{};
    game.start();
    // game.exit();

    return 0;
}
