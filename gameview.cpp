#include <iostream>
#include <string>
#include<thread>
#include<chrono>

//#include <ncurses.h>
//#include "utils.h"
#include "defs.h"
#include "gridview.h"

GridView::GridView(std::shared_ptr <GridLayout> grd, int screen_H, int screen_W) : exit_requested{ false }, grid{ grd },
																				   screen_height{ screen_H },
																				   screen_width{ screen_W }
{
	window_height = grd->size();
	window_width = (*grd)[0].size();
	setup();
}

GridView::GridView(std::shared_ptr <GridLayout> grd)
{
	GridView(grd, SCREEN_LINES, SCREEN_COLS);
}

GridView::~GridView()
{
	endwin();
}

void GridView::terminate()
{
	if (win)
	{
		werase(win);
		delwin(win);
	}
	endwin();
}

void GridView::refresh()
{
	wrefresh(win);
	wgetch(win);
}

void GridView::setup()
{
	initscr();             // start ncurses
	noecho();              // don't print input values
	cbreak();              // terminate curses on CTRL + c
//	check_terminal_size(); // check terminal dimensions
	check_colours();
	start_color(); // enable colour
	curs_set(0);   // make cursor invisible

	win = newwin(0, 0, 0, 0);
	if (win == nullptr)
	{
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
	draw();
	input_loop();
}

void GridView::check_terminal_size()
{
	if (LINES < window_height || COLS < window_width)
	{
		clear();
		endwin();
		std::cout << "Your terminal is too small: min [" << window_width << " x " << window_height << "], currently ["
				  << COLS << " x " << LINES << "]"
				  << std::endl;
		exit(1);
	}
}

void GridView::check_colours()
{
	if (has_colors() == FALSE)
	{
		clear();
		endwin();
		std::cout << "Your terminal does not support colour!" << std::endl;
		exit(1);
	}
}

// Return 32-bit 'chtype' for ncurses display
chtype GridView::cell_string(State cellState)
{
	switch (cellState)
	{
	case State::Obstacle:
		return ('#' | COLOR_PAIR(COL_WALL));
	case State::Food:
		return ('*' | A_BOLD | COLOR_PAIR(COL_FOOD));
	case State::Player:
		return ('@' | A_BOLD | COLOR_PAIR(COL_PLAYER));
	case State::Zombie:
		return ('8' | A_BOLD | COLOR_PAIR(COL_ZOMBIE));
	case State::Empty:
	default:
		return (' ' | COLOR_PAIR(COL_EMPTY));
	}
}

// GridLayout is an alias for vector<vector<State>>
void GridView::draw()
{

	for (auto& row : (*grid))
	{
		for (auto& col: row)
		{
			waddch(win, cell_string(col));
		}
		waddch(win, '\n');
	}
	refresh();
}

//void GridView::start_grid(std::string grid_str)
//{
//
//	for (char& c : grid_str)
//	{
//		switch (c)
//		{
//		case '-':
//			waddch(win, '-' | COLOR_PAIR(COL_WALL));
//			break;
//		case '+':
//			waddch(win, '+' | COLOR_PAIR(COL_WALL));
//			break;
//		case '|':
//			waddch(win, '|' | COLOR_PAIR(COL_WALL));
//			break;
//		case '\n':
//			waddch(win, '\n');
//			break;
//		case ' ':
//		default:
//			waddch(win, ' ' | COLOR_PAIR(COL_EMPTY));
//			break;
//		}
//	}
//	place_player();
//	place_food();
//	place_zombie();
//	refresh();
//	input_loop();
//}


//void GridView::place_player()
//{
//	mvwaddch(win, 1, 1, '@' | A_BOLD | COLOR_PAIR(COL_PLAYER));
//	wrefresh(win);
//	player_pos = { 1, 1 };
//}
//
//void GridView::place_food()
//{
//	int y, x;
//	do
//	{
//		y = Utils::random_int_in_range(9, TEXT_LINES - 9);
//		x = Utils::random_int_in_range(10, TEXT_COLS - 12);
//	} while (!is_move_okay(y, x));
//	mvwaddch(win, y, x, '*' | A_BOLD | COLOR_PAIR(COL_FOOD));
//	wrefresh(win);
//	food_pos = { y, x };
//}
//
//void GridView::place_zombie()
//{
//	int y, x;
//	do
//	{
//		y = Utils::random_int_in_range(15, TEXT_LINES - 1);
//		x = Utils::random_int_in_range(20, TEXT_COLS - 1);
//	} while (!is_move_okay(y, x));
//	mvwaddch(win, y, x, '8' | A_BOLD | COLOR_PAIR(COL_ZOMBIE));
//	wrefresh(win);
//	zombie_pos = { y, x };
//}
//
//void GridView::move_zombie()
//{
//	;
//}
//
//bool GridView::is_move_okay(int y, int x)
//{
//	int testch = mvwinch(win, y, x) & A_CHARTEXT;
//	return (testch == CH_EMPTY || testch == CH_FOOD || testch == CH_ZOMBIE);
//}
//
void GridView::input_loop()
{
	int opt;
	do
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		// float delta = (static_cast<float>(curr - last) / CLOCKS_PER_SEC);
//		update();
//		if (exit_requested)
//			break;
		opt = wgetch(win);
		switch (opt)
		{
		case 'q':
		case 'Q':
			exit_requested = true;
			break;
		}
	} while (!exit_requested);
	wclear(win);
	wgetch(win);
	terminate();
}
//
//void GridView::get_user_input()
//{
//	;
//}
//
//void GridView::update()
//{
//	mvwaddch(win, player_pos.y, player_pos.x, CH_PLAYER | COLOR_PAIR(COL_PLAYER));
//}
//
//bool GridView::game_over()
//{
//	if (zombie_pos.y == food_pos.y && zombie_pos.x == food_pos.x)
//	{
//		player_won = false;
//		return true;
//	}
//	else if (player_pos.y == food_pos.y && player_pos.x == food_pos.x)
//	{
//		player_won = true;
//		return true;
//	}
//	else
//		return false;
//}


