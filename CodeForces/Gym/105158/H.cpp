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

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) res = res * a % Mod;
        a = a * a % Mod;
        p >>= 1;
    }
    return res;
}

i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(2 * n, 0), b(0, 0);
    for (auto &i : a) {
        std::cin >> i;
        if (i != -1) {
            b.push_back(i);
        }
    }
    std::sort(b.begin(), b.end());
    std::vector cnt(n + 1, 0);
    int idx = 0, sum = 0;
    i64 ans = 1;
    for (int i = 0; i < 2 * n; i++) {
        if (a[i] == -1) {
            if (cnt[b[idx]] == 0) {
                std::cout << 0 << '\n';
                return;
            }
            
            (ans *= cnt[b[idx]] * inv(sum) % Mod) %= Mod;
            cnt[b[idx]]--;
            idx++;
            sum--;
        }
        else {
            cnt[a[i]]++;
            sum++;
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}