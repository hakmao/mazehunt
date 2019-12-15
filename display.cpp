#include <iostream>
#include <string>

#include "utils.h"
#include "display.h"
#include "defs.h"

NCursesDisplay::NCursesDisplay(int winH, int winW)
    : win_height{winH}, win_width{winW} {
  setup();
}
NCursesDisplay::~NCursesDisplay() { endwin(); }

void NCursesDisplay::display_grid(Grid &g) {
  // move(1,1);
  // iterate over characters and write to screen
  // line_ctr = 0;
  // col_ctr = 0;
  std::string grid_str = g.to_str();
  // box(stdscr, '#', '#');
  for (char &c : grid_str) {
    switch (c) {
    case '-':
      waddch(win, '-' | COLOR_PAIR(COL_WALL));
      break;
    case '+':
      waddch(win, '+' | COLOR_PAIR(COL_WALL));
      break;
    case '|':
      waddch(win, '|' | COLOR_PAIR(COL_WALL));
      break;
    case '\n':
      waddch(win, '\n');
      break;
    case ' ':
    default:
      waddch(win, ' ' | COLOR_PAIR(COL_EMPTY));
      break;
    }
  }
  wrefresh(win);
  display_player(1,1);
  place_food();
  wgetch(win);
}
void NCursesDisplay::setup() {
  initscr();             // start ncurses
  noecho();              // don't print input values
  cbreak();              // terminate curses on CTRL + c
  check_terminal_size(); // check terminal dimensions
  start_color();         // enable colour

  win = newwin(0, 0, 0, 0);
  if (win == NULL) {
    addstr("Unable to create window");
    refresh();
    getch();
  }
  // box(stdscr, '#', '#');
  init_pair(COL_WALL, COLOR_BLACK, COLOR_RED);
  init_pair(COL_PLAYER, COLOR_CYAN, COLOR_BLUE);
  init_pair(COL_FOOD, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(COL_ZOMBIE, COLOR_RED, COLOR_MAGENTA);
  init_pair(COL_EMPTY, COLOR_WHITE, COLOR_BLACK);
  wbkgd(win, COLOR_PAIR(COL_EMPTY));
}

void NCursesDisplay::check_terminal_size() {
  if (LINES < 24 || COLS < 80) {
    clear();
    endwin();
    std::cout << "Your terminal is too small: min [80 x 24], currently ["
              << COLS << " x " << LINES << "]" << std::endl;
    exit(1);
  }
}

void NCursesDisplay::display_player(int y, int x)
{
    mvwaddch(win, y, x, '@' | A_BOLD | COLOR_PAIR(COL_PLAYER));
    wrefresh(win);
}
void NCursesDisplay::place_food()
{
    int y, x;
    do {
        y = Utils::random_int_in_range(1,TEXT_LINES-1);
        x = Utils::random_int_in_range(1,TEXT_COLS-1);
    } while (!is_move_okay(y,x));
    mvwaddch(win, y, x, '*' | A_BOLD | COLOR_PAIR(COL_FOOD));
    wrefresh(win);
}
bool NCursesDisplay::is_move_okay(int y, int x)
{
    int testch;

    testch = mvwinch(win, y,x);
    return ((testch & A_CHARTEXT) == CH_EMPTY);
}
