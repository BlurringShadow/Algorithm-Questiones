// Created by BlurringShadow at 2021-02-15-下午 10:35

#include "cat_cycle.h"

int main()
{
    using namespace std;

    cat_cycle problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                ""
            })
        {
            is.str(str);
            is.seekg(0);
            is >> problem;

            cout << problem;
        }
    }
    else
        for(auto i = get_from_stream<size_t>(cin); i > 0; --i)
        {
            cin >> problem;
            cout << problem;
        }

    return 0;
}
