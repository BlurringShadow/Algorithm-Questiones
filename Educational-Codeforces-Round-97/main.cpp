// Created by BlurringShadow at 2020-10-27-下午 10:41

#include "minimal_height_tree.h"

int main()
{
    minimal_height_tree problem;
    if constexpr(is_debug)
    {
        std::istringstream is;
        for(auto str : {
                "4 1 4 3 2",
                "2 1 2",
                "3 1 2 3",
                "5 1 2 5 4 3",
                "4 1 2 4 3"
            })
        {
            is.str(str);
            is.seekg(0);
            is >> problem;
            cout << problem;
        }
    }
    else
        for(uint16_t i = get_from_stream(cin); i > 0; --i)
        {
            cin >> problem;
            cout << problem;
        }
    return 0;
}
