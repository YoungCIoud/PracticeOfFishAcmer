#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 5e4, M = 1e5;
std::bitset<N + 5> ans, efc[N + 5], mk;
void init(int n) {
    for (int i = 1; i <= n; i++) {
        efc[i].reset();
    }
    ans.set();
    mk.set();
}

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    init(n);
    std::vector<int> b(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i++) {
        // scanf("%1d", &pre[i]);
        pre[i] = s[i - 1] - '0';
        if (pre[i] == 0) {
            pre[i] = -1;
        }
        pre[i] += pre[i - 1];
    }
    std::cin >> s;
    for (int i = 1; i <= n; i++) {
        b[i] = s[i - 1] - '0';
    }

    std::vector lst(n * 2 + 5, std::vector(0, 0));
    for (int i = n; i >= 1; i--) {
        lst[pre[i] + n].push_back(i);
    }
    auto pos = lst;
    pos[n].push_back(0);
    for (int i = 1; i <= n * 2; i++) {
        lst[i].push_back(0);
    }
    // 处理efc[i]: efc[i][j] = 1 表示pre[i] - pre[j - 1] > 0;
    for (int i = 1; i <= n; i++) {
        efc[i] |= efc[lst[pre[i] + n].back()];
        lst[pre[i] + n].pop_back();
        
        if (pre[i] > pre[i - 1]) {
            efc[i] |= efc[i - 1];
            while (not pos[pre[i - 1] + n].empty() && pos[pre[i - 1] + n].back() < i) {
                efc[i].set(pos[pre[i - 1] + n].back() + 1);
                pos[pre[i - 1] + n].pop_back();
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int val = efc[i][1];
        efc[i] <<= (n - i);
        mk.reset(n - i + 1);
        if (b[i] == 1) {
            if (val == 1) {
                efc[i] |= mk;
            }
        }
        else {
            efc[i].flip();
            if (val == 1) {
                efc[i] ^= mk;
            }
        }

        ans &= efc[i];
    }

    for (int i = n; i >= 1; i--) {
        std::cout << ans[i];
    }
    std::cout << '\n';
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

    system("pause");

    return 0;
}