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
constexpr int N = 12, M = 1e5, Inf = 1e9;

int n;
i64 a[N], sum[N];
std::unordered_set<i64> vis;

// 到第cur个数，已经有bags个袋子，当前的异或和是val
i64 val;
void dfs(int cur, int bags) {
    for (int i = 0; i <= bags; i++) {
        val ^= sum[i];
        sum[i] += a[cur];
        val ^= sum[i];
        if (cur == n - 1) {
            vis.insert(val);
        } else {
            dfs(cur + 1, bags + (i == bags));
        }
        val ^= sum[i];
        sum[i] -= a[cur];
        val ^= sum[i];
    }
    return;
}

void solve()
{
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
    }

    dfs(0, 0);
    std::cout << vis.size() << std::endl;
    return;
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