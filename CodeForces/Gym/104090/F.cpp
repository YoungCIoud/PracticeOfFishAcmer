#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;

    std::unordered_map<std::string, bool> vis;
    while (n--) {
        int m = 0;
        std::cin >> m;

        bool f = true;
        while (m--) {
            std::string s;
            std::cin >> s;

            if (!vis[s] && s.find("bie") < s.size()) {
                std::cout << s << '\n';
                vis[s] = true;
                f = false;
            }
        }
        if (f) {
            std::cout << "Time to play Genshin Impact, Teacher Rice!\n";
        }
    }
    return;
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}