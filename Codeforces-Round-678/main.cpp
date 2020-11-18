#include "bandit_in_a_city.h"

int main()
{
    if constexpr(is_debug)
    {
        bandit_in_a_city::create_from_input(std::istringstream{"3 1 1 3 1 2"});
        bandit_in_a_city::create_from_input(std::istringstream{"3 1 1 3 1 3"});
        bandit_in_a_city::create_from_input(std::istringstream{"3 1 1 2 0 0"});
        bandit_in_a_city::create_from_input(std::istringstream{"5 1 1 1 4 28 0 0 0 0"});
        bandit_in_a_city::create_from_input(
            std::istringstream{
                "10\
                 1 2 3 1 3 4 2 4 6\
                 68 5 44 83 46 92 32 51 2 89"
            }
        );
        bandit_in_a_city::create_from_input(
            std::istringstream{
                "5\
                 1 2 2 1\
                 5 5 5 5 5"
            }
        );
    }
    else bandit_in_a_city::create_from_input(cin);
    return 0;
}
