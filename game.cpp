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

Game::Game()
{
  win_height = SCREEN_LINES;
  win_width = SCREEN_COLS;
  pos_player = {};
  pos_food = {};
  pos_zombie = {};
  rel_food = {};
  score = Score::L;
  goal_reached = false;
  exit_requested = false;
  maze = new Grid(GRID_ROWS, GRID_COLS);
  display = new NCursesDisplay(win_height, win_width);
}
Game::~Game()
{
  delete display;
  display = nullptr;
  delete maze;
  maze = nullptr;
}

void Game::start() {
 
  /* initialize the maze */
  display->display_grid(maze->to_str());
  /* place entities */
  pos_player = display->place_player();
  pos_food = display->place_food();
  pos_zombie = display->place_zombie();
  display->refresh();
}
void Game::exit(){
  delete display;
  delete maze;
}


bool Game::ask_exit() {
  int opt = getch();

  switch (opt) {
  case 'q':
    /* quit */
    // exit_requested = true;
    return true;
    break;
  default:
    return false;
  }
}
