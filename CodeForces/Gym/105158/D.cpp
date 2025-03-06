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

double sqr2 = 1.4142135623730951;

double solve(std::vector<std::pair<i64, i64>> b) {
     std::unordered_set<i64> s;
     for (auto &[x, y] : b) {
          if (s.count(y - x)) {
               return sqr2;
          }
          s.insert(y - x);
     }

     std::sort(b.begin(), b.end(), [](const std::pair<i64, i64> &a, const std::pair<i64, i64> &b) {
          return a.second - a.first < b.second - b.first;
     });
     
     double ans = 0;

     for (int i = 1; i < b.size(); i++) {
          // 两点所连直线的斜率
          if (b[i].second == b[i - 1].second) {
               ans = std::max(ans, 1.0);
               continue;
          }
          double k = (b[i].first - b[i - 1].first) * 1.0 / (b[i].second - b[i - 1].second);
          ans = std::max(ans, sqr2 * std::sin(3.14159265358979323846 / 4.0 + std::atan(k)));
     }

     return ans;
}

int main()
{
     IOS;
     int _t = 1;
     std::cin >> _t;
    
     while (_t--) {
          int n = 0;
          std::cin >> n;
          std::vector<std::pair<i64, i64>> a(n);
          for (int i = 0; i < n; i++) {
               std::cin >> a[i].first >> a[i].second;
          }

          double ans = solve(a);
          for (int i = 0; i < n; i++) {
               std::swap(a[i].first, a[i].second);
               a[i].second = -a[i].second;
          }
          std::cout << std::fixed << std::setprecision(10) << std::max(ans, solve(a)) << '\n';
     }

     sp();

     return 0;
}

/*
2
2
0 0
0 1
3
1 1
2 3
5 8
*/