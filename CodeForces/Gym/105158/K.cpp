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

std::vector<int> g[N + 5], a(N + 1, 0);
bool vis[N + 5];

std::array<int, 2> dfs(int cur, int fa) {
     std::array<int, 2> res = { 1, 0 };
     vis[cur] = true;
     for (auto &to : g[cur]) {
          if (to == fa || 2 * a[cur] < a[to]) {
               continue;
          }

          if (2 * a[to] < a[cur]) {
               res[1]++;
          }
          else {
               auto [cnt, sum] = dfs(to, cur);
               res[0] += cnt;
               res[1] += sum;
          }
     } 
     return res;
}

void solve()
{
     int n = 0;
     std::cin >> n;
     for (int i = 1; i <= n; i++) {
          std::cin >> a[i];
          g[i].clear();
          vis[i] = false;
     }
     for (int i = 1; i < n; i++) {
          int u = 0, v = 0;
          std::cin >> u >> v;
          g[u].push_back(v);
          g[v].push_back(u);
     }

     int ans = 0;
     bool ok = true;
     for (int i = 1; i <= n; i++) {
          if (not vis[i]) {
               auto [cnt, sum] = dfs(i, 0);
               if (sum >= 2) {
                    ok = false;
                    break;
               }
               if (sum == 0) {
                    ans = cnt;
               }
          }
     }

     std::cout << (ok ? ans : 0) << '\n';
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

    sp();

    return 0;
}

/*
3
3
1 2 3
1 2
2 3
5
3 2 2 2 1
1 2
3 1
4 1
1 5
8
699 673 592 276 600 343 369 374
7 6
8 5
4 6
7 1
7 2
1 8
4 3
*/