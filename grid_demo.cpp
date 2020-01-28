#include <iostream>

#include "defs.h"
//#include "grid.h"
#include "grid_tests.h"

int main()
{
	std::cout << "\n=== Create new Grid object from grid state vector ===\n";
	Grid grid1(sample_grid_1);
	std::cout << "\n=== Create another Grid object ===\n";
	Grid grid2(sample_grid_2);
	//
	std::cout << "\n=== Check if new Grid object is equal to first one (expect true) ===\n" << std::endl;
	std::cout << ((grid1 == grid2) ? "- true" : "- false") << std::endl;
	std::cout << "\n=== Check if new Grid object is NOT equal to first one (expect false) ===\n" << std::endl;
	std::cout << ((grid1 != grid2) ? "- true" : "- false") << std::endl;
	std::cout << "\n=== Export representation of grid layout to file ===\n" << std::endl;
	if (grid1.to_file(grid_tests::testfile))
	{
		std::cout << "- write successful!" << std::endl;
	}
	else
	{
		std::cout << "- write failed!" << std::endl;
	}
	std::cout << "\n=== Create Grid object from file, and print to stdout ===\n"
			  << std::endl;
	Grid grid3(grid_tests::testfile);
	std::cout << grid3 << std::endl;

	return 0;
}
