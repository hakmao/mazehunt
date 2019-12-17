#include <iostream>
#include <string>

#include "defs.h"
#include "display.h"
#include "utils.h"

NCursesDisplay::NCursesDisplay(int winH, int winW)
    : win_height{winH}, win_width{winW} {
  setup();
}
NCursesDisplay::~NCursesDisplay() { endwin(); }
void NCursesDisplay::refresh() {
  wrefresh(win);
  wgetch(win);
}
void NCursesDisplay::setup() {
  initscr();             // start ncurses
  noecho();              // don't print input values
  cbreak();              // terminate curses on CTRL + c
  check_terminal_size(); // check terminal dimensions
  check_colours();
  start_color();         // enable colour
  curs_set(0); // make cursor invisible

  win = newwin(0, 0, 0, 0);
  if (win == NULL) {
    addstr("Unable to create window");
    refresh();
    getch();
  }
  nodelay(win, TRUE); // don't block waiting for input
  keypad(stdscr, TRUE);
  keypad(win, TRUE);
  init_pair(COL_WALL, COLOR_BLACK, COLOR_GREEN);
  init_pair(COL_PLAYER, COLOR_BLACK, COLOR_BLUE);
  init_pair(COL_FOOD, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(COL_ZOMBIE, COLOR_MAGENTA, COLOR_RED);
  init_pair(COL_EMPTY, COLOR_BLACK, COLOR_BLACK);
  init_pair(COL_STATUS, COLOR_YELLOW, COLOR_BLACK);
  wbkgd(win, COLOR_PAIR(COL_EMPTY));
}

void NCursesDisplay::start_grid(std::string grid_str) {

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
  place_player();
  place_food();
  place_zombie();
  refresh();
  input_loop();
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
void NCursesDisplay::check_colours() {
  if (has_colors() == FALSE) {
    clear();
    endwin();
    std::cout << "Your terminal does not support colour!" << std::endl;
    exit(1);
  }
}
void NCursesDisplay::place_player() {
  mvwaddch(win, 1, 1, '@' | A_BOLD | COLOR_PAIR(COL_PLAYER));
  wrefresh(win);
  player_pos = {1, 1};
}
void NCursesDisplay::place_food() {
  int y, x;
  do {
    y = Utils::random_int_in_range(9, TEXT_LINES - 9);
    x = Utils::random_int_in_range(10, TEXT_COLS - 12);
  } while (!is_move_okay(y, x));
  mvwaddch(win, y, x, '*' | A_BOLD | COLOR_PAIR(COL_FOOD));
  wrefresh(win);
  food_pos = {y, x};
}
void NCursesDisplay::place_zombie() {
  int y, x;
  do {
    y = Utils::random_int_in_range(15, TEXT_LINES - 1);
    x = Utils::random_int_in_range(20, TEXT_COLS - 1);
  } while (!is_move_okay(y, x));
  mvwaddch(win, y, x, '8' | A_BOLD | COLOR_PAIR(COL_ZOMBIE));
  wrefresh(win);
  zombie_pos = {y, x};
}
void NCursesDisplay::move_zombie()
{
  ;
}
bool NCursesDisplay::is_move_okay(int y, int x) {
  int testch = mvwinch(win, y, x) & A_CHARTEXT;
  return (testch == CH_EMPTY || testch == CH_FOOD || testch == CH_ZOMBIE);
}

void NCursesDisplay::input_loop() {
  int opt;
  do {
    update();
    if (game_over())
      break;
    opt = wgetch(win);
    switch (opt) {
    case KEY_UP:
    case 'w':
    case 'k':
      if ((player_pos.y > 0) && is_move_okay(player_pos.y - 1, player_pos.x)) {
        mvwaddch(win, player_pos.y, player_pos.x, CH_EMPTY | COLOR_PAIR(COL_EMPTY));
        player_pos.y -= 1;
      }
      break;
    case KEY_DOWN:
    case 's':
    case 'j':
      if ((player_pos.y < TEXT_LINES - 1) &&
          is_move_okay(player_pos.y + 1, player_pos.x)) {
        mvwaddch(win, player_pos.y, player_pos.x, CH_EMPTY | COLOR_PAIR(COL_EMPTY));
        player_pos.y += 1;
      }
      break;
    case KEY_LEFT:
    case 'a':
    case 'h':
      if ((player_pos.x > 0) && is_move_okay(player_pos.y, player_pos.x - 1)) {
        mvwaddch(win, player_pos.y, player_pos.x, CH_EMPTY | COLOR_PAIR(COL_EMPTY));
        player_pos.x -= 1;
      }
      break;
    case KEY_RIGHT:
    case 'd':
    case 'l':
      if ((player_pos.x < TEXT_COLS - 1) &&
          is_move_okay(player_pos.y, player_pos.x + 1)) {
        mvwaddch(win, player_pos.y, player_pos.x, CH_EMPTY | COLOR_PAIR(COL_EMPTY));
        player_pos.x += 1;
      }
      break;
    case 'q':
    case 'Q':
      game_running = false;
      break;
    }
    // float delta = (static_cast<float>(curr - last) / CLOCKS_PER_SEC);
  } while (game_running);
  wclear(win);
  wattron(win, COLOR_PAIR(COL_STATUS));
  if (player_won)
    mvwaddstr(win, 10, 25, "Congratulations: You Won!\n");
  else
    mvwaddstr(win, 10, 25, "You Lost! Better luck next time...\n");
  wattroff(win, COLOR_PAIR(COL_STATUS));
  halfdelay(20); // lengthen half-delay 
  wgetch(win);
  endwin();
}
void NCursesDisplay::get_user_input()
{
;
}

void NCursesDisplay::update() {
  mvwaddch(win, player_pos.y, player_pos.x, CH_PLAYER | COLOR_PAIR(COL_PLAYER));
}
bool NCursesDisplay::game_over() {
  if (zombie_pos.y == food_pos.y && zombie_pos.x == food_pos.x) {
    player_won = false;
    return true;
  } else if (player_pos.y == food_pos.y && player_pos.x == food_pos.x) {
    player_won = true;
    return true;
  } else
    return false;
}
