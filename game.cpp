/* game.cpp */

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>

#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "utils.h"
#include "game.h"

template <typename T> T clip(const T &n, const T &lower, const T &upper) {
  return std::max(lower, std::min(n, upper));
}

void Game::check_term_size() {
  if (LINES < 24 || COLS < 80) {
    clear();
    endwin();
    std::cout << "Your terminal is too small: min [80 x 24], currently ["
              << COLS << " x " << LINES << "]" << std::endl;
    exit(0);
  }
}
void Game::place_food()
{
    int y, x;

int y = random_int_in_range(1,TEXT_LINES-1);
}
int Game::start() {
  /* new game state */
  // game_state state;

  /* auxiliary variables */
  float secs;
  clock_t start;
  int ch;

  term_size_check();

  /* create window */
  state.gw_width = COLS;
  state.gw_height = LINES - 1;
  state.gamewin = newwin(state.gw_height, state.gw_width, 0, 0);

  /* initialize the map if any */
  draw_map(&state, map);

  /* start player at [start_length,5] going right */
  state.pos_player.x = 1;
  state.pos_player.y = 2;
  state.score = Score::lose;
  start = clock();

  /* init player */
  wattron(state.gamewin, COLOR_PAIR(C_SNAKE));
  state.snake.clear();
  for (int i = 0; i < start_length; i++) {
    point p = {state.pos.x + 1 - start_length + i, state.pos.y};
    state.snake.push_front(p);
    mvwaddch(state.gamewin, p.y, p.x, SNAKE);
  }
  wattroff(state.gamewin, COLOR_PAIR(C_SNAKE));

  wattron(state.gamewin, COLOR_PAIR(C_SNAKE_H));
  mvwaddch(state.gamewin, state.snake.front().y, state.snake.front().x, SNAKE);
  wattroff(state.gamewin, COLOR_PAIR(C_SNAKE_H));

  /* init food */
  create_food(&state);

  refresh();
  wrefresh(state.gamewin);

  /* speed in m/s */
  state.speed = 2.0;

  /* clocks */
  state.last = 0;

  /* async char read */
  nodelay(stdscr, TRUE);

  /* run */
  state.running = true;
  state.paused = false;

  bool resize = false;

  do {
    resize = state.gw_width != COLS || state.gw_height != LINES - 1;
    if (resize) {
      term_size_check();
      state.gw_width = COLS;
      state.gw_height = LINES - 1;
      wresize(state.gamewin, state.gw_height, state.gw_width);

      draw_map(&state, map);
      redraw_entities(&state);

      wrefresh(state.gamewin);
    } else if (!state.paused) {
      state.curr = clock();

      /* get char async, see nodelay() */
      ch = getch();

      /* test inputted key and determine direction */
      if (ch != ERR) {
        switch (ch) {
        case KEY_UP:
        case 'w':
        case 'k':
          if (state.dir != DOWN)
            do_chdir(&state, state.pos.y - 1, state.pos.x, UP, DOWN);
          break;
        case KEY_DOWN:
        case 's':
        case 'j':
          if (state.dir != UP)
            do_chdir(&state, state.pos.y + 1, state.pos.x, DOWN, UP);
          break;
        case KEY_LEFT:
        case 'a':
        case 'h':
          if (state.dir != RIGHT)
            do_chdir(&state, state.pos.y, state.pos.x - 1, LEFT, RIGHT);
          break;
        case KEY_RIGHT:
        case 'd':
        case 'l':
          if (state.dir != LEFT)
            do_chdir(&state, state.pos.y, state.pos.x + 1, RIGHT, LEFT);
          break;
        case 'q':
          // show quit action
          state.running = false;
          state.curr = state.last = clock();
          break;
        case 'p':
          // pause
          state.paused = true;
          break;
        case 'r':
          // restart
          return R_RESTART_NEW;
        case '+':
          if (cheat && speed_up(&state))
            state.curr = state.last = clock();
          break;
        case '-':
          if (cheat && speed_down(&state))
            state.curr = state.last = clock();
          break;
        }
      }

      float dt = ((float)(state.curr - state.last) / CLOCKS_PER_SEC);
      float secs_per_cell = 1.0F / state.speed;
      if (dt > secs_per_cell) {
        state.last = state.curr;
        /* auto-move */
        switch (state.dir) {
        case UP:
          state.pos.y--;
          break;
        case DOWN:
          state.pos.y++;
          break;
        case RIGHT:
          state.pos.x++;
          break;
        case LEFT:
          state.pos.x--;
          break;
        }
        if (collision_check(&state, state.pos.y, state.pos.x)) {
          /* end */
          state.running = false;
          break;
        } else {
          /* update */
          update(&state, state.pos.y, state.pos.x);
        }
      }

      /* chech food */
      if (state.food.x == state.pos.x && state.food.y == state.pos.y) {
        create_food(&state);
        state.f_eat = true;
        state.score++;
        if (state.score % 20 == 0)
          speed_up(&state);
      }
    } else {
      // paused
      ch = getch();
      if (ch == 'p') {
        state.paused = false;
      }
    }

    /* status */
    attron(COLOR_PAIR(C_STATUS));
    mvhline(LINES - 1, 0, EMPTY, COLS);
    attroff(COLOR_PAIR(C_STATUS));

    secs = ((float)(state.curr - start) / CLOCKS_PER_SEC);
    std::string st = "Score: " + std::to_string(state.score) + " | " +
                     std::to_string((int)secs) + " seconds | " +
                     std::to_string((int)state.speed) + " m/s";

    print_status(" [p]Pause [r]Restart [q]Quit", ALIGN_LEFT,
                 A_BOLD | COLOR_PAIR(C_STATUS));
    print_status(st, ALIGN_RIGHT, COLOR_PAIR(C_STATUS));

    /* title */
    wattron(state.gamewin, COLOR_PAIR(C_BORDER));
    box(state.gamewin, 0, 0);
    if (!state.paused) {
      std::string mapstr;
      mapstr.append(" TSNAKE ");
      mapstr.append(VERSION);
      mapstr.append(" - MAP " + std::to_string(map % N_MAPS + 1) + "  (" +
                    std::to_string(COLS) + "x" + std::to_string(LINES) + ") ");
      mvwaddstr(state.gamewin, 0, 4, mapstr.c_str());
    } else {
      wattron(state.gamewin, COLOR_PAIR(C_GREEN));
      mvwaddstr(state.gamewin, 0, 4, " GAME PAUSED - [p]Continue ");
      wattroff(state.gamewin, COLOR_PAIR(C_GREEN));
    }
    wattroff(state.gamewin, COLOR_PAIR(C_BORDER));

    /* refresh */
    refresh();
    wrefresh(state.gamewin);
  } while (state.running);

  /* done */
  std::string msg3 = "YOUR SCORE: " + std::to_string(state.score);
  std::string msg4 = "You lasted " + std::to_string((int)secs) + " seconds";
  std::string msg1 = "[r] Restart (new map)";
  std::string msg0 = "[s] Restart (same map)";
  std::string msg2 = "[q] Quit";
  int minl = msg1.size();
  int ew_w = clip(COLS / 2, minl, COLS);
  int ew_h = clip(LINES / 2, 4, LINES);
  WINDOW *endw = newwin(ew_h, ew_w, (LINES - ew_h) / 2, (COLS - ew_w) / 2);
  wbkgd(endw, COLOR_PAIR(C_STATUS));
  nodelay(stdscr, FALSE);
  box(endw, 0, 0);

  /* title */
  mvwaddstr(endw, 0, 2, " GAME OVER ");
  /* score and seconds in green */
  mvwaddstr(endw, ew_h / 2 - 3, ew_w / 2 - msg3.size() / 2, msg3.c_str());
  mvwaddstr(endw, ew_h / 2 - 2, ew_w / 2 - msg4.size() / 2, msg4.c_str());

  wattron(endw, A_BOLD);
  mvwaddstr(endw, ew_h / 2 + 1, ew_w / 2 - minl / 2, msg1.c_str());
  mvwaddstr(endw, ew_h / 2 + 2, ew_w / 2 - minl / 2, msg0.c_str());
  mvwaddstr(endw, ew_h / 2 + 3, ew_w / 2 - minl / 2, msg2.c_str());
  wattroff(endw, A_BOLD);

  wrefresh(endw);

  return ask_end();
}

int ask_end() {
  int opt = getch();

  switch (opt) {
  case 'r':
    /* new game, new map */
    return R_RESTART_NEW;
  case 's':
    /* new game, same map */
    return R_RESTART_SAME;
  case 'q':
    /* quit */
    return R_QUIT;
  default:
    return ask_end();
  }
}

void print_status(std::string status, int align, int col) {
  attron(col);
  switch (align) {
  case ALIGN_LEFT:
    move(LINES - 1, 0);
    printw(status.c_str());
    break;
  case ALIGN_RIGHT:
    move(LINES - 1, COLS - status.size() - 1);
    printw(status.c_str());
    break;
  }
  attroff(col);
}

void redraw_entities(game_state *state) {
  /* snake */

  // head
  wattron(state->gamewin, COLOR_PAIR(C_SNAKE_H));
  mvwaddch(state->gamewin, state->snake[0].y, state->snake[0].x, SNAKE);
  wattron(state->gamewin, COLOR_PAIR(C_SNAKE_H));

  // body
  wattron(state->gamewin, COLOR_PAIR(C_SNAKE));
  for (unsigned int i = 1; i < state->snake.size(); i++) {
    mvwaddch(state->gamewin, state->snake[i].y, state->snake[i].x, SNAKE);
  }
  wattron(state->gamewin, COLOR_PAIR(C_SNAKE));

  /* food */

  // reposition
  state->food.x = (int)round((float)state->gw_width * state->food_rel.x);
  state->food.y = (int)round((float)state->gw_height * state->food_rel.y);

  // draw
  wattron(state->gamewin, COLOR_PAIR(C_FOOD));
  mvwaddch(state->gamewin, state->food.y, state->food.x, FOOD);
  wattroff(state->gamewin, COLOR_PAIR(C_FOOD));
}

point rd(game_state *state) {
  point c;
  while (1) {
    c.x = rand() % (state->gw_width - 2) + 1;
    c.y = rand() % (state->gw_height - 2) + 1;

    if ((mvwinch(state->gamewin, c.y, c.x) & A_CHARTEXT) == EMPTY)
      return c;
  }
}

void create_food(game_state *state) {
  point newp = rd(state);
  state->food.x = newp.x;
  state->food.y = newp.y;
  state->food_rel.x = (float)newp.x / (float)state->gw_width;
  state->food_rel.y = (float)newp.y / (float)state->gw_height;
  wattron(state->gamewin, COLOR_PAIR(C_FOOD));
  mvwaddch(state->gamewin, state->food.y, state->food.x, FOOD);
  wattroff(state->gamewin, COLOR_PAIR(C_FOOD));
}

void update(game_state *state, int newy, int newx) {
  point aux = state->snake.front();
  wattron(state->gamewin, COLOR_PAIR(C_SNAKE));
  mvwaddch(state->gamewin, aux.y, aux.x, SNAKE);
  wattroff(state->gamewin, COLOR_PAIR(C_SNAKE));

  point newpoint = {newx, newy};
  state->snake.push_front(newpoint);

  wattron(state->gamewin, COLOR_PAIR(C_SNAKE_H));
  mvwaddch(state->gamewin, newy, newx, SNAKE);
  wattroff(state->gamewin, COLOR_PAIR(C_SNAKE_H));
  if (!state->f_eat) {
    point erase = state->snake.back();
    state->snake.pop_back();
    mvwaddch(state->gamewin, erase.y, erase.x, EMPTY);
  } else {
    state->f_eat = false;
  }
  move(state->pos.y, state->pos.x);
}

void do_chdir(game_state *state, int newy, int newx, int newdir,
              int opposite_dir) {
  if (!collision_check(state, newy, newx)) {
    update(state, newy, newx);
    state->pos.x = newx;
    state->pos.y = newy;
    state->dir = newdir;
    state->curr = state->last = clock();
  } else if (state->dir != opposite_dir) {
    state->running = false;
  }
}

bool speed_up(game_state *state) { return speed_add(state, 1.0); }

bool speed_down(game_state *state) { return speed_add(state, -1.0); }

bool speed_scl(game_state *state, float scale) {
  float cpy = state->speed;
  state->speed = clip(state->speed * scale, 1.0F, 20.0F);
  return cpy != state->speed;
}

bool speed_add(game_state *state, float add) {
  float cpy = state->speed;
  state->speed = clip(state->speed + add, 1.0F, 20.0F);
  return cpy != state->speed;
}

void print_bottom(const char *text) {
  move(LINES - 1, 0);
  printw(text);
}

int out_of_bounds(game_state *state, int y, int x) {
  return y <= 0 || x <= 0 || y >= state->gw_height - 1 ||
         x >= state->gw_width - 1;
}

int collision_check(game_state *state, int y, int x) {
  int testch = mvwinch(state->gamewin, y, x) & A_CHARTEXT;
  return (testch != EMPTY && testch != FOOD) || out_of_bounds(state, y, x);
}

void draw_map(game_state *state, int map) {
  map = map % N_MAPS;
  int y;
  for (y = 0; y < LINES; y++) {
    mvwhline(state->gamewin, y, 0, EMPTY, state->gw_width);
  }

  /* actual map */
  wattron(state->gamewin, COLOR_PAIR(C_WALL));
  switch (map) {
  case 0: {
    /* small pool with a fence */

    // pool
    wattroff(state->gamewin, COLOR_PAIR(C_WALL));
    wattron(state->gamewin, COLOR_PAIR(C_WATER));
    for (int y = state->gw_height * 0.4; y <= state->gw_height * 0.6; y++) {
      mvwhline(state->gamewin, y, state->gw_width / 3, WATER,
               state->gw_width / 3);
    }
    wattroff(state->gamewin, COLOR_PAIR(C_WATER));
    wattron(state->gamewin, COLOR_PAIR(C_WALL));

    // 5 fences
    int tx = state->gw_width * 0.2;
    int ty = state->gw_height * 0.2;
    int bx = state->gw_width * 0.8;
    int by = state->gw_height * 0.8;

    mvwvline(state->gamewin, ty, tx, WALL, by - ty);
    mvwvline(state->gamewin, ty, bx, WALL, by - ty);

    mvwhline(state->gamewin, by, tx, WALL, bx - tx + 1);
    mvwhline(state->gamewin, ty, tx, WALL, state->gw_width * 0.21);
    mvwhline(state->gamewin, ty, state->gw_width * 0.6, WALL,
             state->gw_width * 0.21);

    break;
  }
  case 1: {
    /* two walls with a pool in the middle */

    // pool
    wattroff(state->gamewin, COLOR_PAIR(C_WALL));
    wattron(state->gamewin, COLOR_PAIR(C_WATER));
    for (int y = state->gw_height / 3; y <= state->gw_height * 2 / 3; y++) {
      mvwhline(state->gamewin, y, state->gw_width / 3, WATER,
               state->gw_width / 3);
    }
    wattroff(state->gamewin, COLOR_PAIR(C_WATER));
    wattron(state->gamewin, COLOR_PAIR(C_WALL));

    // 2 walls
    mvwhline(state->gamewin, state->gw_height * 0.2, state->gw_width * 0.3,
             WALL, state->gw_width * 0.7);
    mvwhline(state->gamewin, state->gw_height * 0.8, 0, WALL,
             state->gw_width * 0.7);

    break;
  }
  case 2: {
    /* just one vertical wall */
    mvwvline(state->gamewin, 0, state->gw_width / 2, WALL,
             state->gw_height * 0.7);
    break;
  }
  case 3: {
    /* three walls */
    mvwvline(state->gamewin, 0, state->gw_width / 2, WALL,
             state->gw_height * 0.7);
    mvwhline(state->gamewin, state->gw_height / 2, 0, WALL,
             state->gw_width * 0.3333);
    mvwhline(state->gamewin, state->gw_height / 2, state->gw_width * 0.6666,
             WALL, state->gw_width * 0.3333 + 1);
    break;
  }
  case 4: {
    /* still three walls, centered */
    int hl = state->gw_width * 0.7;
    int vl = state->gw_height * 0.8;
    mvwvline(state->gamewin, (state->gw_height - vl) / 2, state->gw_width / 2,
             WALL, vl);
    mvwhline(state->gamewin, state->gw_height * 0.3333,
             (state->gw_width - hl) / 2, WALL, hl);
    mvwhline(state->gamewin, state->gw_height * 0.6666,
             (state->gw_width - hl) / 2, WALL, hl);
    break;
  }
  }
  wattroff(state->gamewin, COLOR_PAIR(C_WALL));
}
