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
constexpr int N = 2e5, M = 1e5, Inf = 1e9, L = 20;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector st(n + 1, std::vector(L, 0));
    std::vector pre(n + 1, 0);
    std::map<int, std::vector<int>> pos;
    for (int i = 1; i <= n; i++) {
        std::cin >> st[i][0];
        pre[i] = pre[i - 1] ^ st[i][0];
        pos[pre[i]].push_back(i);
    }
    for (int l = 1; l < L; l++) {
        for (int i = 1; i + (1 << l) - 1 <= n; i++) {
            st[i][l] = std::__gcd(st[i][l - 1], st[i + (1 << l - 1)][l - 1]);
        }
    }
    auto quiry = [&](int l, int r) -> int {
        int len = log2(r - l + 1);
        return std::__gcd(st[l][len], st[r - (1 << len) + 1][len]);
    };

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int mn_g = quiry(i, n);
        int l = i, g = st[l][0], tar = g ^ pre[i - 1];
        while (g != mn_g) {
            int r = 0;
            for (int j = L; j >= 0; j--) {
                int rr = r | (1 << j);
                if (rr <= l || (rr <= n && quiry(i, rr) == g)) {
                    r = rr;
                }
            }

            ans += std::upper_bound(pos[tar].begin(), pos[tar].end(), r) - std::lower_bound(pos[tar].begin(), pos[tar].end(), l);
            l = r + 1;
            g = quiry(i, l);
            tar = g ^ pre[i - 1];
        }

        ans += pos[tar].end() - std::lower_bound(pos[tar].begin(), pos[tar].end(), l);
    }

    std::cout << ans - n << '\n';
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