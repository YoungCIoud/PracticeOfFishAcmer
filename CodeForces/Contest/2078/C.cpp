#include<bits/stdc++.h>

#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr u64 Mod = 1'0000'0000'0000'1029, MAX = -1;
constexpr int N = 5e5, Q = 5e5;

void solve() {
    int n = 0;
    std::cin >> n;
    std::vector a(2 * n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }

    std::sort(a.begin(), a.end(), std::greater<int>());
    a.push_back(a[0] + a.back());
    for (int i = 1; i + 1 < 2 * n; i += 2) {
        std::swap(a[i], a[i + 1]);
        a[2 * n] += a[i + 1] - a[i];
    }
    std::swap(a[2 * n], a[2 * n - 1]);
    for (int i = 0; i <= 2 * n; i++) {
        std::cout << a[i] << " \n"[i == 2 * n];
    }
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }
    return 0;
}
