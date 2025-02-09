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

void solve()
{
    int n = 0, m = 0;
    std::string a, b;
    std::cin >> n >> m >> a >> b;
    if (a.length() < b.length()) {
        std::swap(a, b);
        std::swap(n, m);
    }

    std::vector<int> cnta(26, 0), cntb(26, 0);
    for (auto &c : a) {
        cnta[c - 'a']++;
    }
    for (auto &c : b) {
        cntb[c - 'a']++;
    }

    int cen = a.length() - b.length(); // 中心
    int len = n - cen; // 两侧
    for (int i = 0; i < 26; i++) {
        if (cnta[i] > cntb[i]) {
            len -= cntb[i];
            cnta[i] -= cntb[i];
            cntb[i] = 0;
        }
        else {
            len -= cnta[i];
            cntb[i] -= cnta[i];
            cnta[i] = 0;
        }
    }

    for (int i = 0; i < 26 && cen >= 2; i++) {
        while (cen >= 2 && cnta[i] >= 2) {
            cen -= 2;
            cnta[i] -= 2;
        }
    }

    std::cout << len + cen / 2 << '\n';
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