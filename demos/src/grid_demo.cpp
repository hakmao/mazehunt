#include <iostream>

#include "defs.h"
//#include "grid.h"
#include "grid_data.h"

int main()
{
	std::cout << "\n=== Create first Grid object from grid state vector ===\n";
	Grid grid1(grid_data::sample_grid_1);
	std::cout << "\n=== Create second Grid object ===\n";
	Grid grid2(grid_data::sample_grid_2);
    std::cout << "\n=== Create third Grid object (using same vector as the first) ===\n";
    Grid grid3(grid_data::sample_grid_1);
	//
	std::cout << "\n=== Check that second Grid object is NOT equal to first one (expect false) ===\n" << std::endl;
	std::cout << ((grid1 == grid2) ? "- true" : "- false") << std::endl;
    std::cout << "\n=== Check that first Grid object is equal to the third one (expect true) ===\n" << std::endl;
    std::cout << ((grid1 == grid3) ? "- true" : "- false") << std::endl;
	std::cout << "\n=== Export representation of grid layout to file ===\n" << std::endl;
	if (grid1.to_file("grid_demo.grid"))
	{
		std::cout << "- write successful!" << std::endl;
	}
	else
	{
		std::cout << "- write failed!" << std::endl;
	}
	std::cout << "\n=== Create Grid object from file, and print to stdout ===\n"
			  << std::endl;
	Grid grid4("grid_demo.grid");
	std::cout << grid4 << std::endl;

	return 0;
}
