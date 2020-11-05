#include "putting_bricks_in_the_wall.h"

int main()
{
    if constexpr(is_debug)
    {
        putting_bricks_in_the_wall::create_from_input(
            std::istringstream{
                "4\n\
                 3\n\
                 S11\n\
                 011\n\
                 00F\
                 4\n\
                 S010\n\
                 0001\n\
                 1000\n\
                 111F\n\
                 3\n\
                 S10\n\
                 101\n\
                 01F\n\
                 5\n\
                 S0101\n\
                 00000\n\
                 01111\n\
                 11111\n\
                 0001F\n"
            }
        );
    }
    else putting_bricks_in_the_wall::create_from_input(cin);
    return 0;
}
