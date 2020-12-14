#include "shurikens.h"

int main()
{
    using namespace std;

    shurikens s;
    if constexpr(is_debug)
    {        
        istringstream is;
        for(auto str : {
                "4 + + - 2 + - 3 + - 1 - 4",
                "1 - 1 +",
                "3 + + + - 2 - 1 - 3",
                "10 "
                "+ "
                "- 3 "
                "+ "
                "+ "
                "+ "
                "+ "
                "- 1 "
                "- 7 "
                "- 9 "
                "- 10 "
                "+ "
                "+ "
                "+ "
                "- 4 "
                "- 5 "
                "- 8 "
                "+ "
                "- 6 "
                "+ "
                "- 2"
            })
        {
            is.str(str);
            is.seekg(0);
            is >> s;

            cout << s;
        }
    }
    else
    {
        cin >> s;
        cout << s;
    }

    return 0;
}
