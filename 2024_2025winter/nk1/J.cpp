// 异或等于gcd
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
std::vector<int> p;
bool vis[1001];
std::vector<std::array<int, 2>> fac;

void dfs(int idx, int f, std::vector<int> &res) {
    res.push_back(f);
    for (int i = idx; i < fac.size(); i++) {
        for (int j = 0, k = fac[i][0]; j < fac[i][1]; j++, k *= fac[i][0]) {
            dfs(i + 1, f * k, res);
        }
    }
}

std::vector<int> find(int x) {
    fac.clear();
    for (auto &f : p) {
        if (f * f > x) {
            break;
        }
        if (x % f == 0) {
            fac.push_back({ f, 0 });
        }
        while (x % f == 0) {
            fac.back()[1]++;
            x /= f;
        }
    }
    if (x != 1) {
        fac.push_back({ x, 1 });
    }

    std::vector<int> res;
    dfs(0, 1, res);
    return res;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector cnt(N + 1, 0);
    for (int i = 0; i < n; i++) {
        int x = 0;
        std::cin >> x;
        cnt[x]++;
    }
    
    i64 ans = 0;
    for (int i = 1; i <= N; i++) {
        if (cnt[i] == 0) {
            continue;
        }
        // std::cout << i << ":\t";
        for (auto f : find(i)) {
            // std::cout << f << ' ';
            int j = i ^ f;
            if (std::__gcd(i, j) == f && j <= N) {
                ans += 1ll * cnt[i] * cnt[j];
            }
        }
        // std::cout << '\n';
    }
    std::cout << ans / 2ll << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;

    for (int i = 2; i <= 1000; i++) {
        if (not vis[i]) {
            p.push_back(i);
        }
        for (auto &f : p) {
            if (i * f > 1000) {
                break;
            }
            vis[i * f] = true;
            if (i % f == 0) {
                break;
            }
        }
    }
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}