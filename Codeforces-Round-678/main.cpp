#include "binary_search.h"

int main()
{
    if constexpr(is_debug)
    {
        binary_search::create_from_input(std::istringstream{"4 1 2"});
        binary_search::create_from_input(std::istringstream{"4 3 2"});
        binary_search::create_from_input(std::istringstream{"2 1 1"});
        binary_search::create_from_input(std::istringstream{"2 2 0"});
        binary_search::create_from_input(std::istringstream{"7 7 6"});
        binary_search::create_from_input(std::istringstream{"4 4 3"});
        binary_search::create_from_input(std::istringstream{"123 42 24"});
        binary_search::create_from_input(std::istringstream{"1000 501 501"});
    }
    else binary_search::create_from_input(cin);
    return 0;
}
