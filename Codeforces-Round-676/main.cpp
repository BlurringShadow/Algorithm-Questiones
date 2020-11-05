#include "palindromifier.h"

int main()
{
    if constexpr(is_debug)
    {
        palindromifier::create_from_input(std::istringstream{"abac"});
        palindromifier::create_from_input(std::istringstream{"acccc"});
        palindromifier::create_from_input(std::istringstream{"hannah"});
    }
    else palindromifier::create_from_input(cin);
    return 0;
}
