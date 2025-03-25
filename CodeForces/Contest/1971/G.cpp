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

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, Inf = 1e9;

int a[N + 5];
int h[N + 5], top;
std::vector<std::multiset<int>> hp(N + 5);

void solve()
{
    int n = 0;
    std::cin >> n;
    top = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        h[top++] = (a[i] >> 2);
    }
    std::sort(h, h + top);

    for (int i = 0; i < n; i++) {
        int idx = std::lower_bound(h, h + top, a[i] >> 2) - h;
        hp[idx].insert(a[i]);
    }

    for (int i = 0; i < n; i++) {
        int idx = std::lower_bound(h, h + top, a[i] >> 2) - h;
        std::cout << *hp[idx].begin() << ' ';
        hp[idx].erase(hp[idx].begin());
    }
    std::cout << '\n';

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

    sp();

    return 0;
}