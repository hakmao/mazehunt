#ifndef SEARCH_H
#define SEARCH_H

#define DEBUG false

#include <deque>
#include <list>
#include "grid.h"

//using std::deque;
using std::list;
using Path = list<Cell>;

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
	list <Cell> path{};
	vector <CandidateCell> openList{};
    vector <Cell> visited{};
	GridLayout grid{};

	// members
	bool is_valid_cell(int x, int y);
    bool has_been_visited(int x, int y);
	int calculate_heuristic(int x, int y, Cell g);
	void sort_open_list();
    void print_open_list() const;
	void add_to_open_list(int x, int y, int g, int h);
	void expand_neighbours(const CandidateCell& current, Cell goal);
	void prune_path();

public:
	PathFinder(GridLayout grd);
	bool search(Cell init, Cell goal);
    int path_size() const;
	Path get_path();
	void print_path() const;
};

#endif //SEARCH_H
