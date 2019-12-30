#ifndef SEARCH_H
#define SEARCH_H

#define DEBUG true

#include <deque>
#include "grid.h"

using std::deque;

// directional deltas
const int delta[4][2]{{ -1, 0 },
					  { 0,  -1 },
					  { 1,  0 },
					  { 0,  1 }};

struct CandidateCell
{
	int x;
	int y;
	int g;
	int h;

	CandidateCell(int a, int b, int c, int d) : x{ a }, y{ b }, g{ c }, h{ d }
	{
	}; // for use with emplace_back()
};

bool compare_cells(CandidateCell const & a, CandidateCell const & b);

class PathFinder
{
private:
	// data
//	Cell goal;
	deque <Cell> path{};
	vector <CandidateCell> openList{};
	GridLayout grid{};

	// members
	bool is_valid_cell(int x, int y);

	int calculate_heuristic(int x, int y, Cell g);

	void sort_open_list();

	void add_to_open_list(int x, int y, int g, int h);

	void expand_neighbours(const CandidateCell& current, Cell goal);

public:
	PathFinder(GridLayout grd);

	bool search(Cell init, Cell goal);

	deque <Cell> get_path();

	void print_path();

	void print_open_list();

};

#endif //SEARCH_H
