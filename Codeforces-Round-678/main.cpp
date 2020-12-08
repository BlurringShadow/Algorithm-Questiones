#include "complicated_computations.h"

int main()
{
    if constexpr(is_debug)
    {
        complicated_computations::create_from_input(std::istringstream{"3 1 2 3"}); //5 
        complicated_computations::create_from_input(std::istringstream{"3 1 3 2"}); //3 
        complicated_computations::create_from_input(std::istringstream{"5 1 1 1 1 1"}); //1
        complicated_computations::create_from_input(std::istringstream{"5 1 4 3 1 2"}); //6
        complicated_computations::create_from_input(
            std::istringstream{
                "51 45 37 1 8 4 41 35 15 17 2 7 48 20 42 41 5 26 25 37 1 19 43 3 49 33 2 45 43 39 14 1 21 22 17 18 8 49 24 35 26 22 43 45 1 3 17 1 16 35 33 5"
            }
        ); //5
        complicated_computations::create_from_input(
            std::istringstream{
                "100 100 2 3 99 5 6 7 8 9 10 65 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 48 32 83 79 35 36 37 38 39 40 41 42 43 44 45 46 47 31 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 11 66 67 68 69 70 71 72 73 80 75 76 77 78 34 74 81 82 33 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 4 1"
            }
        ); //3
        {
            static constexpr auto max = complicated_computations::value_range.second;
            std::stringstream is;
            is << max;
            for(complicated_computations::uint i = 0; i < max; ++i)  
                is << ' ' << i + 1;
            complicated_computations::create_from_input(is);
        }
    }
    else complicated_computations::create_from_input(cin);
}
