#include <iostream>
#include "gameview.h"

GridLayout grid_1 = {
		{ State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle },
		{ State::Obstacle, State::Player,   State::Obstacle, State::Empty,    State::Zombie,   State::Obstacle },
		{ State::Obstacle, State::Empty,    State::Obstacle, State::Empty,    State::Obstacle, State::Obstacle },
		{ State::Obstacle, State::Food,    State::Empty,    State::Empty,     State::Empty,    State::Obstacle },
		{ State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle }};

GridLayout grid_2 = {
		{ State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle },
		{ State::Obstacle, State::Food,     State::Obstacle, State::Empty,    State::Zombie,   State::Obstacle },
		{ State::Obstacle, State::Empty,    State::Obstacle, State::Empty,    State::Empty,    State::Obstacle },
		{ State::Obstacle, State::Player,   State::Empty,    State::Empty,    State::Empty,    State::Obstacle },
		{ State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle, State::Obstacle }};

int main()
{
	auto grid_ptr = std::make_shared<GridLayout>(grid_1);
	GameView gV{grid_ptr};

	return 0;
}