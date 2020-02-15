#include <iostream>
#include <string>
#include<thread>
#include<chrono>

//#include <ncurses.h>
//#include "utils.h"
#include "defs.h"
#include "gameview.h"


GameView::GameView(std::shared_ptr <GridLayout> grd, int screen_H, int screen_W) : exit_requested{ false }, grid{ grd },
                                                                                   screen_height{ screen_H },
                                                                                   screen_width{ screen_W }
{
    grid_height = grd->size();
    grid_width = (*grd)[0].size();
    if (!is_grid_size_okay())
    {
        std::cout << "The maze is too large for the specified screen size!" << std::endl;
        exit(1);
    }
    setup();
}

GameView::GameView(std::shared_ptr <GridLayout> grd)
{

    GameView(grd, SCREEN_LINES, SCREEN_COLS);
}


GameView::~GameView()
{
    endwin();
}

void GameView::terminate()
{
    if (win)
    {
        werase(win);
        delwin(win);
    }
    endwin();
}

void GameView::refresh()
{
    wrefresh(win);
    wgetch(win);
}

void GameView::setup()
{
    initscr();             // start ncurses
    noecho();              // don't print input values
    cbreak();              // terminate curses on CTRL + c
//	check_terminal_size(); // check terminal dimensions
    if (!is_terminal_size_okay())
    {
        endwin();
        std::cout << "Your terminal is too small! (must be at least 80 x 24)" << std::endl;
        exit(1);
    }
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
    init_pair(COL_WALL, COLOR_BLACK, COLOR_BLUE);
    init_pair(COL_PLAYER, COLOR_WHITE, COLOR_GREEN);
    init_pair(COL_FOOD, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(COL_ZOMBIE, COLOR_MAGENTA, COLOR_RED);
    init_pair(COL_EMPTY, COLOR_BLACK, COLOR_BLACK);
    init_pair(COL_STATUS, COLOR_YELLOW, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(COL_STATUS));
    wbkgd(win, COLOR_PAIR(COL_EMPTY));
    draw();
    input_loop();
}

bool GameView::is_grid_size_okay() const
{
    // check that grid will fit into screen
    if (grid_height > screen_height || grid_width > screen_width)
    {
        return false;
    }
    else
        return true;
}

bool GameView::is_terminal_size_okay() const
{
    // check that terminal is not smaller than required screen size
    if (LINES < screen_height || COLS < screen_width)
    {
        return false;
    }
    else
        return true;
}

void GameView::check_colours() const
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
chtype GameView::cell_string(State cellState)
{
    switch (cellState)
    {
        case State::Obstacle: return ('#' | COLOR_PAIR(COL_WALL));
        case State::Food: return ('*' | A_BOLD | COLOR_PAIR(COL_FOOD));
        case State::Player: return ('@' | A_BOLD | COLOR_PAIR(COL_PLAYER));
        case State::Zombie: return ('8' | A_BOLD | COLOR_PAIR(COL_ZOMBIE));
        case State::Empty:
        default: return (' ' | COLOR_PAIR(COL_EMPTY));
    }
}

// GridLayout is an alias for vector<vector<State>>
void GameView::draw()
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

//void GameView::start_grid(std::string grid_str)
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


//void GameView::place_player()

//{
//	mvwaddch(win, 1, 1, '@' | A_BOLD | COLOR_PAIR(COL_PLAYER));
//	wrefresh(win);
//	player_pos = { 1, 1 };
//}
//
//void GameView::place_food()

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
//void GameView::place_zombie()
//

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
//void GameView::move_zombie()

//{
//	;
//}
//
//bool GameView::is_move_okay(int y, int x)

//{
//	int testch = mvwinch(win, y, x) & A_CHARTEXT;
//	return (testch == CH_EMPTY || testch == CH_FOOD || testch == CH_ZOMBIE);
//}
//
void GameView::input_loop()
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
            case 'Q': exit_requested = true;
                break;
        }
    } while (!exit_requested);
    wclear(win);
    wgetch(win);
    terminate();
}

//
//void GameView::get_user_input()
//
//{
//	;
//}
//
//void GameView::update()
//
//{
//	mvwaddch(win, player_pos.y, player_pos.x, CH_PLAYER | COLOR_PAIR(COL_PLAYER));
//}
//
//bool GameView::game_over()
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


