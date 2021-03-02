// Created by BlurringShadow at 2021-02-28-下午 9:51
#include "k-th-largest-value.h"

int main()
{
    using namespace std;

    problem_t problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "5 5\n"
                "1 1 0 1 0\n"
                "2 3\n"
                "1 2\n"
                "2 3\n"
                "2 1\n"
                "2 5"
            })
        {
            is.str(str);
            is.seekg(0);
            is >> problem;

            cout << problem;
        }
    }
    else //for(auto i = get_from_stream<size_t>(cin); i > 0; --i)
    {
        cin >> problem;
        cout << problem;
    }

    return 0;
}
