//
// Created by Johannes Flieger on 27/12/2019.
//

#ifndef MAZEHUNT_GRIDSTATE_H
#define MAZEHUNT_GRIDSTATE_H

struct Cell
{
	int x;
	int y;
};

enum class State
{
	Empty = 0,
	Obstacle,
	Food,
	Player,
	Zombie
};

using GridLayout = vector<vector<State>>;

#endif MAZEHUNT_GRIDSTATE_H

