#include "reorder.h"

int main()
{
    if constexpr(is_debug)
        reorder::create_from_input(
            std::istringstream{
                "2\
                 3 8    2 5 1\
                 4 4    0 1 2 3"
            }
        );
    else reorder::create_from_input(cin);
    return 0;
}
