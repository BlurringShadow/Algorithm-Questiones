#include "new_technique.h"

int main()
{
    using namespace std;

    if constexpr(is_debug)
    {
        new_technique::create_from_input(
            istringstream{
                "2\
                 2 3\
                 6 5 4\
                 1 2 3\n\
                 1 6\
                 2 5\
                 3 4\
                 3 1\n\
                 2\
                 3\
                 1\
                 3 1 2"
            }
        );
    }
    else new_technique::create_from_input(cin);

    return 0;
}
