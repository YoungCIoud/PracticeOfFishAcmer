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
constexpr int N = 13, M = 1e5, Inf = 1e9;

std::string s;
// 预处理出 3 的幂
std::vector p3(N + 1, 1);

// 传入左端点和区间长度的次数
std::pair<int, int> dfs(int l, int n) {
    // 递归出口
    if (n == 0) {
        return { s[l] - '0', 1 };
    }

    std::vector son{ dfs(l, n - 1), dfs(l + p3[n - 1], n - 1), dfs(l + 2 * p3[n - 1], n - 1) };
    std::sort(son.begin(), son.end());
    int val = 0, cost = 0;
    if (son[0].first == son[2].first) {
        val = son[0].first;
        int sum = 0, mx = 0;
        for (int i = 0; i < 3; i++) {
            sum += son[i].second;
            mx = std::max(mx, son[i].second);
        }
        cost = sum - mx;
    }
    else {
        val = son[1].first;
        if (val == 0) {
            cost = std::min(son[0].second, son[1].second);
        }
        else {
            cost = std::min(son[1].second, son[2].second);
        }
    }

    return { val, cost };
}

void solve()
{
    int n = 0;
    std::cin >> n;
    std::cin >> s;

    std::cout << dfs(0, n).second << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    for (int i = 1; i <= N; i++) {
        p3[i] = 3 * p3[i - 1];
    }
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}