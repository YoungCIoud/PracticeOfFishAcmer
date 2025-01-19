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
constexpr int N = 2e5, M = 2e5, Inf = 1e9;

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    for (; p; a = a * a % Mod, p >>= 1) {
        if (p & 1) {
            (res *= a) %= Mod;
        }
    }
    return res;
}

i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}

i64 C[N + 5];

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector vis(n + 1, false);
    std::vector s(m, std::pair<int, int>{});
    // 取反使排序后对于左端点相同的区间，较长的会在前面
    for (auto &[l, r] : s) {
        std::cin >> l >> r;
        if (l == r) {
            vis[l] = true;
        }
        else if (l == 1 && r == n) {
            vis[0] = true;
        }
        r = -r;
    }

    // { i, i } 和 { 1, n } 是一定可以加的
    if (not vis[0]) {
        s.push_back({ 1, -n });
    }
    for (int i = 1; i <= n; i++) {
        if (not vis[i]) {
            s.push_back({ i, -i });
        }
    }

    std::sort(s.begin(), s.end());

    std::vector siz(s.size(), 0);
    for (int i = 0; i < s.size(); i++) {
        const auto &[l, r] = s[i];
        int j = i + 1;
        while (j < s.size()) {
            if (s[j].second < r) {
                break;
            }
            siz[i]++;
            j = std::upper_bound(s.begin(), s.end(), std::make_pair( -s[j].second, 0 )) - s.begin();
        }
    }

    i64 ans = 1;
    for (auto &i : siz) {
        if (i) {
            (ans *= C[i - 1]) %= Mod;
        }
    }
    std::cout << ans << '\n';
    
    return;
}

int main()
{
    C[0] = 1;
    for (int i = 1; i <= N; i++) {
        C[i] = 1ll * (4 * i - 2) * inv(i + 1) % Mod * C[i - 1] % Mod;
    }

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