// 思维
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
constexpr int N = 1e6, M = 1e6, Inf = 1e9;
i64 a[M], cnt[N];

bool solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        std::cin >> a[i];
    }

    std::vector w(n, std::vector(m, 0));
    std::vector pq(m, std::priority_queue<std::pair<int, int>>{});
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        cnt[i] = 0;
        for (int j = 0; j < m; j++) {
            int c = 0;
            std::cin >> c;
            if (a[j] < c) {
                cnt[i]++;
                pq[j].push({ -c, i });
            }
        }
        if (cnt[i] == 0) {
            q.push(i);
        }
        for (int j = 0; j < m; j++) {
            std::cin >> w[i][j];
        }
    }

    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        for (int i = 0; i < m; i++) {
            a[i] += w[cur][i];
            while (not pq[i].empty() && -(pq[i].top().first) <= a[i]) {
                auto [val, idx] = pq[i].top();
                pq[i].pop();
                if ((--cnt[idx]) == 0) {
                    q.push(idx);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (cnt[i] != 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "YES" : "NO") << '\n';
    }

    return 0;
}