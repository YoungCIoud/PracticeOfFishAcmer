#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr i64 N = 1e10, K = 1e10, L = 1e5;

i64 f[11][L][2];

int parse(i64 x) {
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

void solve()
{
    i64 k = 0ll, m = 0ll;
    std::cin >> k >> m;
    i64 ans = 0;
    if (k > L  || k * k >= m) {
        for (int st = 1; st <= 90; st++) {
            for (i64 n = st; n <= m; n += k) {
                ans += (n - parse(n)) % k == 0;
            }
        }
    }
    else {
        i64 p9[] = { 0, 9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999, 9999999999 };
        std::vector<int> dig;
        i64 len = m;
        while (len) {
            dig.push_back(len % 10);
            len /= 10;
        }
        len = dig.size();
        for (int i = 0; i < len; i++) {
            p9[i] %= k;
        }
        
        f[0][0][0] = 10;
        f[0][0][1] = dig[0] + 1;
        for (int i = 1; i < len; i++) {
            for (int j = 0; j < k; j++) {
                if (f[i - 1][j][0] == 0) {
                    continue;
                }
                for (int d = 0; d < 10; d++) {
                    f[i][(j + d * p9[i]) % k][0] += f[i - 1][j][0];
                }
                for (int d = 0; d < dig[i]; d++) {
                    f[i][(j + d * p9[i]) % k][1] += f[i - 1][j][0];
                }
                f[i][(j + dig[i] * p9[i]) % k][1] += f[i - 1][j][1];
            }
        }
        ans = f[len - 1][0][1] - 1;
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