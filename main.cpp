// #include <iostream>
#include <string>
// #include <ncurses.h>
#include "defs.h"
#include "grid.h"
#include "display.h"

int main(int argc, char *argv[])
{
    // std::cout << "Creating maze...\n";
    Grid maze(GRID_ROWS, GRID_COLS);
    NCursesDisplay ncdisplay(TEXT_LINES, TEXT_COLS);
    ncdisplay.display_grid(maze);
    ncdisplay.display_player(1,1);

    return 0;
}
