// Created by BlurringShadow at 2021-02-18-下午 10:58

#include "three_swimmers.h"

int main()
{
    using namespace std;

    problem_t problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "9 5 4 8",
                "2 6 10 9",
                "10 2 5 10",
                "10 9 9 9"
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
