//
// Created by Johannes Flieger on 27/12/2019.
//
#include <iostream>
#include "search.h"

int main()
{
	Grid grid("search.grid");
	Cell init{ 4, 1 };
	Cell goal{ 1, 3 };
	PathFinder finder(grid.get_state());
	bool path_found = finder.search(init, goal);
	if (path_found)
	{
		std::cout << "Path found!" << std::endl;
		deque <Cell> path = finder.get_path();
		std::cout << "Path size = " << path.size() << std::endl;
		while (!path.empty())
		{
			auto next_cell = path.front();
			std::cout << "[" << next_cell.x << "," << next_cell.y << "], ";
			path.pop_front();
		}
		std::cout << std::endl;
		std::cout << "Path size = " << path.size() << std::endl;
#if DEBUG
		std::cout << "The path is still stored in the PathFinder object: " << std::endl;
		finder.print_path();
#endif
	}

	return 0;
}



