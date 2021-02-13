// Created by BlurringShadow at 2021-02-07-下午 10:50

#include "yet_another_string_game.h"

int main()
{
    using namespace std;

    yet_another_string_game problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                "a",
                "bbbb",
                "az"
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
