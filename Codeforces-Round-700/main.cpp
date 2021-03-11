// Created by BlurringShadow at 2021-02-07-下午 10:50

#include "the_great_hero.h"

int main()
{
    using namespace std;

    problem_t problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "3 17\n1\n2\n16\n",
                "10 999\n3\n10 20 30\n100 50 30\n",
                "1000 1000\n4\n200 300 400 500\n1000 1000 1000 1000",
                "999 999\n1\n1000\n1000",
                "999 999\n1\n1000000\n999"
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
