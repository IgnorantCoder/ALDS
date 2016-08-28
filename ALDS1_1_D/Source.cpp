#include <iostream>
#include <algorithm>

constexpr int max_r();
constexpr int max_size();
constexpr int min_value();
int solve0(const int n, int const* r);
int solve1(const int n, int const* r);

int main()
{
    int n;
    std::cin >> n;

    constexpr int N = max_size();
    int r[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> r[i];
    }

    const int ret = solve1(n, r);
    std::cout << ret;
    
    return 0;
}

constexpr int max_r()
{
    return 1e+9;
}

constexpr int max_size()
{
    return 2e+5;
}

constexpr int min_value()
{
    return 1 - max_r();
}

/**
@brief simple solution.
@detail O(n^2)
*/
int solve0(const int n, int const* r)
{
    int ret = min_value();
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            ret = std::max(ret, r[i] - r[j]);
        }
    }
    return ret;
}

/**
@brief hold min value.
@detail O(n)
*/
int solve1(const int n, int const* r)
{
    int ret = min_value();
    int temp_min = r[0];
    for (int i = 1; i < n; ++i) {
        ret = std::max(ret, r[i] - temp_min);
        temp_min = std::min(r[i], temp_min);
    }
    return ret;
}
