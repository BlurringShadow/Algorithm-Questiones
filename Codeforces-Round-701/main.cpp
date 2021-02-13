// Created by BlurringShadow at 2021-02-12-下午 11:03

#include "add_and_divide.h"

int main()
{
    using namespace std;

    add_and_divide problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "9 2",
                "1337 1",
                "1 1",
                "50000000 4",
                "991026972 997",
                "1234 5678"
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
