#include <random>
#include "utils.h"

int Utils::random_int_in_range(int lower, int upper)
{
    std::random_device rdm;                            // Obtain seed for MT engine
    std::mt19937 gen(rdm());                           // Mersenne twister engine seeded with rdm();
    std::uniform_int_distribution<> dis(lower, upper); // integer range

    return dis(gen);
}

int Utils::random_index(int collection_size)
{
    return random_int_in_range(0, collection_size - 1);
}
