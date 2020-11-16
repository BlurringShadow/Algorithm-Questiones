#include "prime_square.h"

int main()
{
    if constexpr(is_debug) prime_square::create_from_input(std::istringstream{"2 3 4 5 6 100"});
    else prime_square::create_from_input(cin);
    return 0;
}
