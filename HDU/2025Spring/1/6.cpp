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
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::unordered_map<int, int> mp;

    for (int i = 0; i < n; i++) {
        std::vector a(3, 0);
        for (int j = 0; j < 3; j++) {
            std::cin >> a[j];
        }
        std::unordered_set<int> s;
        for (int j = 0; j < 3; j++) {
            std::array<int, 2> v = { a[j], a[(j + 1) % 3] };
            int v3 = a[(j + 2) % 3];
            for (int k = 0; k < 2; k++) {
                if ((v[k] - v[1 - k]) % v3 == 0 && (v[k] - v[1 - k]) / v3 >= 0) {
                    s.insert((v[k] - v[1 - k]) / v3);
                }
            }
        }
        for (auto x : s) {
            mp[x]++;
        }
    }

    for (auto &[num, cnt] : mp) {
        if (cnt == n) {
            std::cout << num << '\n';
            return;
        }
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

    sp();

    return 0;
}