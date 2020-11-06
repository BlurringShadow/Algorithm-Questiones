#include "hexagons.h"

int main()
{
    if constexpr(is_debug)
        hexagons::create_from_input(
            std::istringstream{
                "2\
                 -3 1\
                 1 3 5 7 9 11\
                 1000000000 1000000000\
                 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000"
            }
        );
    else hexagons::create_from_input(cin);
    return 0;
}
