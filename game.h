#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include "display.h"
#include "grid.h"

enum class Score { W, L };

class Game {
public:
  Game();
  ~Game();
  void start();
  void exit();

private:
  // game window size
  int win_width, win_height;
  // current position of the player
  // Point pos_player;
  // current position of the monster
  // Point pos_zombie;
  // current food position
  // Point pos_food;
  // current food relative position
  // PointF rel_food;
  // score
  Score score;
  // flag that goes up when we reach the goal
  // bool game_over;
  // flag that goes up when the user quits
  // bool exit_requested;
  // timers
  clock_t curr, last;
  // game window
  // WINDOW *win;
  // maze grid
  Grid *maze;
  // display
  NCursesDisplay *display;

  /* private methods */
  // void draw_grid();
  // void redraw_entities();
  // void place_entities();
  // bool is_move_okay(int y, int x);
  // int out_of_bounds(int y, int x);
  // int collision_check(int y, int x);
  // void update(int newy, int newx);
  // void print_bottom(std::string text);
  // void print_status(std::string status, int align, int col);
  bool ask_exit();
};

#endif
