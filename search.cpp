#include <iostream>
#include <algorithm> //for sort()
#include "search.h"

using std::abs;

bool compare_cells(const CandidateCell& a, const CandidateCell& b){
	int f1 = a.g + a.h; // f-score is the sum of cost and heuristic value
	int f2 = b.g + b.h;
	return f1 > f2;
}

PathFinder::PathFinder(GridLayout g): grid{g}{}

//
bool PathFinder::is_valid_cell(int x, int y)
{
	bool on_grid_x = (x >= 0 && x < grid.size());
	bool on_grid_y = (y >= 0 && y < grid[0].size());
	if (on_grid_x && on_grid_y)
	{
		State s = grid[x][y];
		switch(s)
		{
		case State::Empty:
		case State::Food:
		case State::Player:
			return true;
			break;
		case State::Zombie:
		case State::Obstacle:
		case State::Visited:
		default:
			return false;
		}
	}
	return false;
}

int PathFinder::calculate_heuristic(int x, int y, Cell g)
{
	return abs(g.x - x) + abs(g.y - y); // Manhattan distance
}

// Sort cells in descending order (i.e., highest f-score first)
void PathFinder::sort_open_list()
{
	std::sort(openList.begin(), openList.end(), compare_cells);
}

// Add a candidate cell to the open list, and mark it as visited
void PathFinder::add_to_open_list(int x, int y, int g, int h)
{
	openList.emplace_back(x, y, g, h);
	grid[x][y] = State::Visited;
}

// Expand current cell's neighbours and add them to the open list
void PathFinder::expand_neighbours(const CandidateCell& current, Cell goal)
{
	// Get current cell's data
	int x = current.x;
	int y = current.y;
	int g = current.g;

	// Loop through potential neighbours
	for (int i{0}; i < 4; i++)
	{
		int new_x = x + delta[i][0];
		int new_y = y + delta[i][1];

		// Check that neighbour's coordinates are on the grid, and have not been visited
		if (is_valid_cell(new_x, new_y))
		{
			// Increment g-value and add neighbour to open list
			int new_g = g + 1;
			int new_h = calculate_heuristic(new_x, new_y, goal);
			add_to_open_list(new_x, new_y, new_g, new_h);
		}
	}
}

bool PathFinder::search(Cell init, Cell goal)
{
	// Set start and finish cells
	// Add start cell to the open list
	int x = init.x;
	int y = init.y;
	int g = 0;
	int h = calculate_heuristic( x, y, goal);
	add_to_open_list(x, y, g, h);

	while(openList.size() > 0)
	{
#if DEBUG
		print_open_list();
#endif
		// Get the next cell (with highest value)
		sort_open_list();
#if DEBUG
		std::cout << "After sorting:" << std::endl;
		print_open_list();
#endif
		auto current = openList.back();
		openList.pop_back();
		int x = current.x;
		int y = current.y;
		path.emplace_back(x, y);
#if DEBUG
		print_path();
#endif
		// Check if we've reached the goal
		if (x == goal.x && y == goal.y)
		{
			return true;
		}
		// If we're not done, expand search to current cell's neighbours
		expand_neighbours(current, goal);
	}
	// We've run out of open cells to search, and haven't found a path
	return false;
}

deque<Cell> PathFinder::get_path(){
	return path;
}

void PathFinder::print_path()
{
	std::cout << "Path: ";
	for (auto it = path.begin(); it != path.end(); it++)
	{
		std::cout << "<" << it->x << "," << it->y << ">,";
	}
	std::cout << std::endl;
}
void PathFinder::print_open_list()
{
	std::cout << "Open list: ";
	for (auto it = openList.begin(); it != openList.end(); it++)
	{
		std::cout << "<" << it->x << "," << it->y << "," << it->g << "," << it->h << ">, ";
	}
	std::cout << std::endl;
}

