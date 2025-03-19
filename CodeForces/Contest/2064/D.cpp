#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, L = 30, Inf = 1 << 30;
int w[N + 5], suf[N + 5], pre[N + 5][L + 5];
int f(int x) {
    int msb = 0;
    while(x != 1) {
        x >>= 1;
        msb++;
    }
    return msb;
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    suf[n + 1] = 0;
    w[0] = Inf;
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i];
        int msb = f(w[i]);
        for (int j = 0; j < L; j++) {
            pre[i][j] = msb < j ? pre[i - 1][j] : i;
        }
    }
    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] ^ w[i];
    }
    
    while (q--) {
        int x = 0;
        std::cin >> x;

        int msb = f(x), L = pre[n][msb];
        while ((x ^ suf[L + 1]) >= w[L]) {
            if (x == suf[L]) {
                L--;
                break;
            }

            msb = f(x ^ suf[L]);
            L = pre[L - 1][msb];
        }
        std::cout << n - L << " ";
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

    return 0;
}