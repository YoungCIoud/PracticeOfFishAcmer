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
constexpr int N = 2e5;

int r[N + 5], in[N + 5], d[N + 5];

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        in[i] = 0;
        d[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> r[i];
        in[r[i]]++;
    }

    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    int ans = 0;
    while (not q.empty()) {
        int cur = q.front();
        ans = std::max(ans, d[cur]);
        q.pop();
        int to = r[cur];

        d[to] += d[cur];
        in[to]--;
        if (in[to] == 0) {
            q.push(to);
        }
    }
    std::cout << ans + 2 << '\n';
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

    // sp();

    return 0;
}