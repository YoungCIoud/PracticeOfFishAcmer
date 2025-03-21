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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 10, Inf = 1 << 30;
int a[N + 5][M + 5], b[M + 5];

void solve() {
    int n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i][0];
        sum += a[i][0];
        for (int j = 1; j <= m; j++) {
            a[i][j] = Inf;
        }
    }
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    for (int u = 1; u < (1 << m); u++) {
        int effc = Inf - 1, cnt = 0;
        for (int bit = 0; bit < m; bit++) {
            if (u >> bit & 1) {
                cnt++;
                effc &= b[bit];
            }
        }

        for (int i = 0; i < n; i++) {
            a[i][cnt] = std::min(a[i][cnt], a[i][0] & effc);
        }
    }

    std::vector<int> sub;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sub.push_back(a[i][j + 1] - a[i][j]);
        }
    }
    std::sort(sub.begin(), sub.end());
    for (int i = 0; i < k; i++) {
        sum += sub[i];
    }
    std::cout << sum << '\n';
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
