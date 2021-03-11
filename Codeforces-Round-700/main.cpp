// Created by BlurringShadow at 2021-02-07-下午 10:50

#include "searching_local_minimum.h"

int main()
{
    using namespace std;

    problem_t problem;
    /*
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {"5 3 2 1 4 5"})
        {
            is.str(str);
            is.seekg(0);
            is >> problem;

            cout << problem;
        }
    }
    else //for(auto i = get_from_stream<size_t>(cin); i > 0; --i)
    */
    {
        cin >> problem;
        cout << problem;
    }

    return 0;
}
