// Created by BlurringShadow at 2020-11-01-下午 7:29

#include "divide_and_sum.h"

int main()
{
    using namespace std;

    divide_and_sum problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "1 1 4",
                "2 2 1 2 1",
                "5 1 1 1 1 1 2 2 2 2 2",
                "5 13 8 35 94 9284 34 54 69 123 846"
            })
        {
            is.str(str);
            is.seekg(0);
            is >> problem;

            cout << problem;
        }
    }
    else
    {
        cin >> problem;
        cout << problem;
    }

    return 0;
}
