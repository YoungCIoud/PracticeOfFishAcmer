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
    int n = 0, x = 0, y = 0;
    std::string s;
    std::cin >> n >> x >> y >> s;
    if (x > y) {
        std::swap(x, y);
    }

    // [l, r)
    std::vector<std::array<int, 2>> ans;
    for (int i = 0; i + x <= n; i++) {
        if (s[i] == '1') {
            continue;
        }

        ans.push_back({ i, i + x });
        for (int j = i; j < i + x; j++) {
            s[j] ^= 1;
        }
    }

    int g = std::__gcd(x, y);
    for (int i = 0; i + g <= n; i++) {
        if (s[i] == '1') {
            continue;
        }
        int l = i, r = l + g;
        for (int j = l; j < r; j++) {
            s[j] ^= 1;
        }
        while (l < r) {
            if (r - l < y) {
                ans.push_back({ l - x, l });
                l -= x;
            }
            else {
                ans.push_back({ l, l + y });
                l += y;
            }
        }
    }

    if (s == std::string(n, '1')) {
        assert(ans.size() <= n * n);
        std::cout << ans.size() << '\n';
        for (auto &[l, r] : ans) {
            std::cout << l + 1 << ' ' << r << '\n';
        }
    }
    else {
        std::cout << "-1\n";
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