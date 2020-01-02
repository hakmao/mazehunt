#ifndef GRIDVIEW_H
#define GRIDVIEW_H

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

class GridView
{
public:
	GridView(std::shared_ptr<GridLayout> grd);
	~GridView();
	void terminate();
//	bool exit_requested_by_user() const;
//	void update(Cell old, Cell new);
//	Cell next_cell() const;
//	void update(GridLayout);

private:
	// data
	bool exit_requested;
	std::shared_ptr<GridLayout> grid;
//	GridLayout grid{};
//	deque<Cell> player_path{};
	WINDOW* win; // TODO: Use smart pointer instead of raw pointer
	int window_height;
	int window_width;
	int screen_height;
	int screen_width;
	// methods
	void setup();
	void draw();
	void refresh();
	void input_loop();
	void check_terminal_size();
	void check_colours();
	chtype cell_string(State cellState);
//	void get_user_input();
};

#endif
