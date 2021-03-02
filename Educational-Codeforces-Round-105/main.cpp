// Created by BlurringShadow at 2021-03-02-下午 10:50
#include "abc_string.h"

int main()
{
    using namespace std;

    problem_t problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "AABBAC",
                "CACA",
                "BBBBAC",
                "ABCA"
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
