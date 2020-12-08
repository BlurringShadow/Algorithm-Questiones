// Created by BlurringShadow at 2020-10-31-下午 11:39

#include "frequency_sort.h"
#include <fmt/format.h>

int main()
{
    for(const auto num : frequency_sort::frequencySort(vector<int>(100, -29)))
        fmt::print("{} ", num);
    fmt::print("\n");
    return 0;
}