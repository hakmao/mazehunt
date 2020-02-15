//
// Created by Johannes Flieger on 27/12/2019.
//
#include <iostream>
#include "search.h"

int main()
{
	Grid grid("search.grid");
    PathFinder finder(grid.global_state());
	Cell init{ 1, 1 };
	Cell goal{ 1, 4 };
	std::cout << "=== Search Demo ===" << std::endl;
	std::cout << "Start: [" << init.x << ", " << init.y << "] " << std::endl;
    std::cout << "Goal:  [" << goal.x << ", " << goal.y << "] " << std::endl;
//    std::cout << "Grid:\n" << grid << std::endl;
	bool path_found = finder.search(init, goal);
	if (path_found)
	{
		std::cout << "=== Path found! :) ===" << std::endl;

	}
	else
    {
        std::cout << "=== Path not found :( ===" << std::endl;
    }
    std::cout << "Path size = " << finder.path_size() << std::endl;
    std::cout << "Final path:" << std::endl;
    std::cout << "Raw path: " << std::endl;
    finder.print_path();
    std::cout << "Pruned path: " << std::endl;
    Path p = finder.get_path();
    for (auto it = p.begin(); it != p.end(); it++)
    {
        std::cout << "[" << it->x << "," << it->y << "] => ";

    }
    std::cout << "END" << std::endl;
    std::cout << "Grid:\n" << grid << std::endl;

	return 0;
}



