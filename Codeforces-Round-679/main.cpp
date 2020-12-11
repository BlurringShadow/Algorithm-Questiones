#include "perform_easily.h"

int main()
{
    using namespace std;

    if constexpr(is_debug)
    {
        /*
        perform_easily::create_from_input(istringstream{"1 2 3 4 5 6\n2\n10 20"}); //5
        perform_easily::create_from_input(istringstream{"1 4 100 10 30 5\n6\n101 104 105 110 130 200"}); //0
        */
        perform_easily::create_from_input(istringstream{"1 1 2 2 3 3\n7\n13 4 11 12 11 13 12"}); //7
    }
    else perform_easily::create_from_input(cin);

    return 0;
}
