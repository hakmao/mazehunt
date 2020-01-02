#ifndef GameView_H
#define GameView_H

#include <chrono>
#include <string>
#include <ncurses.h>
#include <time.h>
#include <memory.h>

#include "grid.h"

struct Point
{
	int y;
	int x;
	chtype ch;
};

class GameView
{
public:

	GameView(std::shared_ptr <GridLayout> grd);

	GameView(std::shared_ptr <GridLayout> grd, int screen_H, int screen_W);

	~GameView();

	void terminate();
//	bool exit_requested_by_user() const;
//	void update(Cell old, Cell new);
//	Cell next_cell() const;
//	void update(GridLayout);

private:
	// data
	bool exit_requested;
	std::shared_ptr <GridLayout> grid;
//	GridLayout grid{};
//	deque<Cell> player_path{};
	WINDOW* win; // TODO: Use smart pointer instead of raw pointer
	int grid_height;
	int grid_width;
	int screen_height;
	int screen_width;

	// methods
	void setup();

	void draw();

	void refresh();

	void input_loop();

	bool is_terminal_size_okay() const;

	bool is_grid_size_okay() const;

	void check_colours() const;

	chtype cell_string(State cellState);
//	void get_user_input();
};

#endif
