#include <iostream>

#include "defs.h"
#include "grid.h"

std::string testfile = "test.grid";
vector <vector<State>> sample_grid_1 = {
		{ State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle },
		{ State::Obstacle, State::Player,   State::Obstacle, State::Empty,    State::Zombie,   State::Obstacle },
		{ State::Obstacle, State::Empty,    State::Obstacle, State::Empty,    State::Obstacle, State::Obstacle },
		{ State::Obstacle, State::Empty,    State::Empty,    State::Food,     State::Empty,    State::Obstacle },
		{ State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle }};

vector <vector<State>> sample_grid_2 = {
		{ State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle },
		{ State::Obstacle, State::Food,     State::Obstacle, State::Empty,    State::Zombie,   State::Obstacle },
		{ State::Obstacle, State::Empty,    State::Obstacle, State::Empty,    State::Empty,    State::Obstacle },
		{ State::Obstacle, State::Player,   State::Empty,    State::Empty,    State::Empty,    State::Obstacle },
		{ State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle }};

int main()
{
	std::cout << "\n=== Create new Grid object from grid state vector ===\n";
	Grid grid1(sample_grid_1);
	std::cout << "\n- number of rows (expect 5): " << grid1.rows() << std::endl;
	std::cout << "\n- number of cols(expect 6): " << grid1.cols() << std::endl;
	std::cout << "\n- size (expect 5 x 6 = 30): " << grid1.size() << std::endl;
	std::cout << "\n=== Create another Grid object ===\n";
	Grid grid2(sample_grid_2);
	std::cout << "\n=== Check if new Grid object is equal to first one (expect false) ===\n" << std::endl;
	std::cout << ((grid1 == grid2) ? "- true" : "- false") << std::endl;
	std::cout << "\n=== Check if new Grid object is NOT equal to first one (expect true) ===\n" << std::endl;
	std::cout << ((grid1 != grid2) ? "- true" : "- false") << std::endl;
	std::cout << "\n=== Import integer representation from exported file and replace grid state ===\n" << std::endl;
	bool file_was_read = grid2.from_file(testfile);
	if (file_was_read)
	{
		std::cout << "- read successful:\n";
		std::cout << grid2 << std::endl;
	}
	else
		std::cout << "- read failed!" << std::endl;
	//
	std::cout << "\n=== Check if new Grid object is equal to first one (expect true) ===\n" << std::endl;
	std::cout << ((grid1 == grid2) ? "- true" : "- false") << std::endl;
	std::cout << "\n=== Check if new Grid object is NOT equal to first one (expect false) ===\n" << std::endl;
	std::cout << ((grid1 != grid2) ? "- true" : "- false") << std::endl;
	std::cout << "\n=== Export representation of grid layout to file ===\n" << std::endl;
	if (grid1.to_file(testfile))
	{
		std::cout << "- write successful!" << std::endl;
	}
	else
	{
		std::cout << "- write failed!" << std::endl;
	}
	std::cout << "\n=== Create empty Grid object, import integer representation from file, and print to stdout ===\n"
			  << std::endl;
	Grid grid3{};
	file_was_read = grid3.from_file(testfile);
	if (file_was_read)
	{
		std::cout << "- read successful:\n";
		std::cout << grid3 << std::endl;
	}
	else
		std::cout << "- read failed!" << std::endl;


	return 0;
}
