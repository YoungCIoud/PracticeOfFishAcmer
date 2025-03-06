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
constexpr int N = 2e5, M = 1e5, Inf = 1e9;

void solve() {
     int n = 0;
     std::cin >> n;
     std::vector a(n, 0);
     std::vector lst(n + 1, -1);
     int cnt = 0;
     for (int i = 0; i < n; i++) {
         std::cin >> a[i];
          if (lst[a[i]] == -1) {
               cnt++;
          }
          lst[a[i]] = i;
     }

     std::vector vis(n + 1, false);
     for (int i = 0; i < n; i++) {
          if (vis[i]) {
               continue;
          }
          int r = lst[a[i]];
          for (int j = i; j <= r; j++) {
               vis[j] = true;
               r = std::max(r, lst[a[j]]);
          }

          std::sort(a.begin() + i, a.begin() + r + 1, std::greater<int>());
     }

     std::vector dp(n + 1, Inf);
     dp[0] = 0;
     for (int i = 0; i < n; i++) {
          *std::lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
     }
     int len = n;
     while (dp[len] == Inf) {
          len--;
     }
     std::cout << cnt - len << '\n';
}

int main()
{
    IOS;
    int _t = 1;
//     std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}

/*
10
1 10 2 6 10 8 9 4 4 5
*/