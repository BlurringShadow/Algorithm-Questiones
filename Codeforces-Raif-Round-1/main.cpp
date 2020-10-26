// Created by BlurringShadow at 2020-10-20-下午 1:46

#include "carrots_for_rabbits.h"

int main()
{
#ifdef NDEBUG
    carrots_for_rabbits::create_from_input(cin);
#else
    carrots_for_rabbits::create_from_input(std::istringstream{"3 6 5 3 1"});
    carrots_for_rabbits::create_from_input(std::istringstream{"1 4 19"});
    carrots_for_rabbits::create_from_input(std::istringstream{"1 3 1000000"});
#endif
    return 0;
}
