// Created by BlurringShadow at 2021-03-06-下午 10:32
#include "planet_lapituletti.h"

int main()
{
    using namespace std;

    problem_t problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "24 60\n 12:21",
                "24 60\n 23:59",
                "90 80\n 52:26",
                "1 100\n 00:01",
                "10 10\n 04:04"
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
