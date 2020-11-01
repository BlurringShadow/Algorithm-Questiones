#include "xor_wice.h"

int main()
{
    if constexpr(is_debug)
    {
        xor_wice::create_from_input(std::istringstream{"1 6 12"});
    }
    else xor_wice::create_from_input(cin);
    return 0;
}
