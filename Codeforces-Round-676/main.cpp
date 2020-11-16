#include "swedish_heroes.h"

int main()
{
    if constexpr(is_debug)
    {
        swedish_heroes::create_from_input(std::istringstream{"4 5 6 7 8"});
        swedish_heroes::create_from_input(std::istringstream{"5 4 -5 9 -2 1"});
        swedish_heroes::create_from_input(std::istringstream{"5 -56 101 87 0 -24"});
        swedish_heroes::create_from_input(
            std::istringstream{
                "11 559227829 -118401759 491756598 -50857099 491152214 -500410377 141179566 -414122877 144131087 -460846619 791017750"
            }
        );
    }
    else swedish_heroes::create_from_input(cin);
    return 0;
}
