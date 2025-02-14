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
constexpr int N = 1e5, M = 2e5, Inf = 1e9, MXR = 3e5;

std::vector<std::array<int, 2>> R[MXR + 5];
std::unordered_set<int> mp[M + 5];

int ans;
void add(int x, int y) {
    if (x >= 0 && y >=0 && x <= M && y <= M && mp[x].count(y) != 0) {
        ans++;
    }
}

void solve()
{
    for (int i = 1; i * i <= MXR; i++) {
        for (int j = 1; j < i && i * i + j * j <= MXR; j++) {
            if ((i + j) % 2 == 0 || std::__gcd(i, j) != 1) {
                continue;
            }

            int a = 2 * i * j;
            int b = i * i - j * j;
            int c = i * i + j * j;
            for (int k = 1; c * k <= MXR; k++) {
                R[c * k].push_back({ a * k, b * k });
            }
        }
    }

    int n = 0;
    std::cin >> n;
    std::vector p(n, std::array<int, 3>{});
    for (auto &[x, y, r] : p) {
        std::cin >> x >> y >> r;
        x += N, y += N;
        mp[x].insert(y);
    }

    for (auto &[x, y, r] : p) {
        if (r > MXR) {
            continue;
        }
        add(x + r, y);
        add(x - r, y);
        add(x, y + r);
        add(x, y - r);
        for (auto &[d1, d2] : R[r]) {
            add(x + d1, y + d2);
            add(x + d1, y - d2);
            add(x - d1, y + d2);
            add(x - d1, y - d2);
            add(x + d2, y + d1);
            add(x + d2, y - d1);
            add(x - d2, y + d1);
            add(x - d2, y - d1);
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