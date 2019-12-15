#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

struct point {
  int x, y;
};
struct pointf {
  float x, y;
};

enum class Score { W, L };

enum class Entity {
    Player,
    Food,
    Zombie
};

class Game {
public:
  Game();
  void start_game();

private:
  // current position of the player
  point pos_player;
  // current position of the monster
  point pos_monster;
  // current food position
  point pos_food;
  // current food relative position
  pointf rel_food;
  // score
  Score score;
  // flag that goes up when we reach the goal
  bool goal_reached;
  // timers
  clock_t curr, last;
  // game window size
  int win_width, win_height;
  // game window
  WINDOW *win;

  /* private methods */
  bool is_move_okay(int y, int x);
  void check_term_size();
  void draw_grid();
  void place_food();
  void update(int newy, int newx);
  int out_of_bounds(int y, int x);
  int collision_check(int y, int x);
  void print_bottom(std::string text);
  void print_status(std::string status, int align, int col);
  int ask_end();
  void redraw_entities();
};

#endif
