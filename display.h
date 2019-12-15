#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <ncurses.h>
#include "grid.h"

class NCursesDisplay
{
    public:
        NCursesDisplay(int winh, int winw);
        ~NCursesDisplay();
        void display_grid(Grid& g);
        void display_player(int y, int x);
        void display_monster(int y, int x);
        void display_food(int y, int x);
        void place_food();
        bool is_move_okay(int y, int x);

    private:
        int win_height, win_width;
        WINDOW* win;
        void setup();
        void check_terminal_size();
}; 

#endif
