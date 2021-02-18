// Created by BlurringShadow at 2021-02-18-下午 10:58

#include "shifting_stacks.h"

int main()
{
    using namespace std;

    problem_t problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "2 1 2",
                "2 1 0",
                "3 4 4 4",
                "2 0 0",
                "3 0 1 0",
                "3 0 1 1",
                "4 1000000000 1000000000 1000000000 1000000000"
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
