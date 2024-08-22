#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

bool solve()
{
    i64 n = 0, k = 0;
    std::cin >> n >> k;
    if (n == k) return true;
    else if (k == 1) return n & 1;
    else return false;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        std::cout << (solve() ? "A" : "B");
    }

    system("pause");

    return 0;
}