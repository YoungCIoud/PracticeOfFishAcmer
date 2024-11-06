#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
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
std::string s = "qkj";
struct Node {
    int mn;
    int via;
    int to;
    bool ok;
};

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector card(3, std::vector(n, 0));
    for (auto &v : card) {
        for (auto &i : v) {
            std::cin >> i;
        }
    }

    std::vector mn(3, std::vector(n, 0));
    for (int i = 0; i < 3; i++) {
        mn[i][n - 1] = n - 1;
    }
    std::vector chain(n, std::array<int, 2>{});
    for (int i = n - 2; ~i; i--) {
        for (int j = 0; j < 3; j++) {
            mn[j][i] = mn[j][i + 1];
        }
        for (int j = 0; j < 3; j++) {
            if (card[j][i] > card[j][mn[j][i]]) {
                chain[i] = { j, mn[j][i] };
                for (int k = 0; k < 3; k++){
                    if (card[k][i] < card[k][mn[k][i]]) {
                        mn[k][i] = i;
                    }
                }
            }
        }
    }

    if (chain[0][1]) {
        std::cout << "Yes\n";
        std::queue<std::array<int, 2>> ans;
        int cur = 0;
        while (cur != n - 1) {
            ans.push(chain[cur]);
            cur = chain[cur][1];
        }
        std::cout << ans.size() << '\n';
        while (not ans.empty()) {
            std::cout << s[ans.front()[0]] << ' ' << ans.front()[1] + 1 << '\n';
            ans.pop();
        }
    }
    else {
        std::cout << "No\n";
    }
    return;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}