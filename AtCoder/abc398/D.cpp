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
constexpr int N = 1e5, M = 1e5, Inf = 1e9;
std::multiset<std::pair<int, int>> cnt;

void solve()
{
    int n = 0, R = 0, C = 0;
    std::string s;
    std::cin >> n >> R >> C >> s;
    
    int r = 0, c = 0;
    cnt.insert({ 0, 0 });
    for (auto &ch : s) {
        if (ch == 'N') {
            r--;
        }
        else if (ch == 'S') {
            r++;
        }
        else if (ch == 'E') {
            c++;
        }
        else {
            c--;
        }
        cnt.insert({ r, c });

        std::cout << (cnt.count({ r - R, c - C }) != 0 ? 1 : 0);
    }
    std::cout << '\n';
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

    system("pause");

    return 0;
}