#include <iostream>
#include <vector>

using std::vector;

enum class State
{
    Empty = 0,
    Obstacle = 1,
    Food = 2,
    Player = 3,
    Zombie = 4
};
int int_value(State s)
{
    return static_cast<int>(s);
}

vector<State> states = {State::Obstacle, State::Player, State::Obstacle, State::Food,
                        State::Empty,    State::Zombie, State::Obstacle};
vector<int> nums = {1, 3, 1, 2, 0, 4, 1};

int main()
{
    vector<int> ints_from_states{};
    for (auto it = states.begin(); it != states.end(); it++)
    {
        ints_from_states.push_back(int_value(*it));
    }
    std::cout << "Convert states to integer values: " << ((ints_from_states == nums) ? "success" : "fail") << std::endl;
    for (auto i : ints_from_states)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    vector<State> states_from_ints{};
    for (auto it = nums.begin(); it != nums.end(); it++)
    {
        states_from_ints.push_back(static_cast<State>(*it));
    }
    std::cout << "Convert integers to states: " << ((states_from_ints == states) ? "success" : "fail") << std::endl;

    return 0;
}
