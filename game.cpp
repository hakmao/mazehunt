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
  score = Score::L;
  // game_over = false;
  // exit_requested = false;
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
void Game::exit(){
  delete display;
  delete maze;
}

void Game::start() {
  /* setup the starting maze configuration */
  display->start_grid(maze->to_str());
}
