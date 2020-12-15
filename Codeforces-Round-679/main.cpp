#include "solo_mid_oracle.h"

int main()
{
    using namespace std;

    solo_mid_oracle problem;
    if constexpr(is_debug)
    {
        istringstream is;
        for(auto str : {
                // 1
                "1 1 1 1",
                // 2
                "2 2 2 2",
                // 1
                "1 2 3 4",
                // 5
                "4 3 2 1",
                // 534
                "228 21 11 3",
                // -1
                "239 21 11 3",
                // 500000500000
                "1000000 1 1000000 1"
            })
        {
            is.str(str);
            is.seekg(0);
            is >> problem;

            cout << problem;
        }
    }
    else
        for(auto i = get_from_stream<uint32_t>(cin); i > 0; --i)
        {
            cin >> problem;
            cout << problem;
        }

    return 0;
}
