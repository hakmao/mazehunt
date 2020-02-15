#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <chrono>
#include <string>
#include <ncurses.h>
#include <time.h>

struct Point {
  int y; // y-coord ncurses display 
  int x; // x-coord ncurses display 
};

struct PointF {
  float y;
  float x;
};
enum class Entity {
    Player,
    Food,
    Zombie
};

class NCursesDisplay
{
    public:
        // data
        bool player_won{false};
        // methods
        NCursesDisplay(int winh, int winw);
        ~NCursesDisplay();
        void refresh();
        void start_grid(std::string g);
        bool move_player(Point p);
        Point get_position(Entity);
        bool ask_exit();
        bool goal_status();

    private:
        // data
        int win_height, win_width;
        Point player_pos;
        Point food_pos;
        Point zombie_pos;
        bool game_running{true};
        // std::deque<Point> path;
        // timers
        // clock_t start, end;
        // size_t frame_duration{10000};
        WINDOW* win;
        // methods
        void setup();
        void input_loop();
        void check_terminal_size();
        void check_colours();
        bool is_move_okay(int y, int x);
        void place_player();
        void place_food();
        void place_zombie();
        void move_zombie();
        void show();
        void update();
        bool game_over();
        void heuristic();
        void get_user_input();
}; 

#endif
