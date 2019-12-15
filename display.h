#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <string>
#include <ncurses.h>

struct Point {
  int y; // y-coord ncurses display 
  int x; // x-coord ncurses display 
};

struct PointF {
  float y;
  float x;
};

class NCursesDisplay
{
    public:
        NCursesDisplay(int winh, int winw);
        ~NCursesDisplay();
        void refresh();
        void display_grid(std::string g);
        // void move_entity(Entity, Point dest);
        Point place_player();
        Point place_food();
        Point place_zombie();
        bool is_move_okay(int y, int x);

    private:
        int win_height, win_width;
        WINDOW* win;
        void setup();
        void check_terminal_size();
}; 

#endif
