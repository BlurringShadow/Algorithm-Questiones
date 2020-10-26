#include <iostream>

using std::cout;
using std::cin;

/*
 * For a given array a consisting of n integers and a given integer m.
 * Find if it is possible to reorder elements of the array a in such a way that n∑i=1 n∑j=i a[j]/j equals m.
 * It is forbidden to delete elements as well as insert new elements.
 * Please note that no rounding occurs during division, for example, 5/2=2.5.
 * Input
 * The first line contains a single integer t — the number of test cases (1≤t≤100).
 * The test cases follow, each in two lines.
 * 
 * The first line of a test case contains two integers n and m (1≤n≤100, 0≤m≤106).
 * The second line contains integers a1,a2,…,an (0≤ai≤106) — the elements of the array.
 * 
 * Output
 * For each test case print "YES",
 * if it is possible to reorder the elements of the array in such a way
 * that the given formula gives the given value, and "NO" otherwise.
 *  */
class Reorder
{
public:

    static void create_from_input()
    {
        unsigned test_case_count;
        
        for(cin >> test_case_count; test_case_count > 0; --test_case_count)
        {
            size_t array_size, target, sum = 0;
            cin >> array_size >> target;
            for(; array_size > 0; --array_size)
            {
                size_t num;
                cin >> num;
                sum += num;
            }

            cout << (sum == target ? "YES" : "NO") << '\n';
        }
    }
};

int main()
{
    Reorder::create_from_input();
    return 0;
}
