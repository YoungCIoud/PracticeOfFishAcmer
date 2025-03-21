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

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 5e5, M = 1e9;
int n, k;

std::vector<i64> work(std::vector<int> &a, std::string &s) {
    // f[i] 前 i 个位置里第 i 个位置有基站的合法放置的最小花费
    std::vector f(n + 1, 0ll);
    std::deque<int> q;
    q.push_back(0);
    for (int i = 1; i <= n; i++) {
        f[i] = a[i] + f[q.front()];
        while (not q.empty() && (s[i] == '1' || f[q.back()] >= f[i])) {
            q.pop_back();
        }
        q.push_back(i);
        while (q.front() <= i - k) {
            q.pop_front();
        }
    }
    return f;
}

void solve()
{
    std::cin >> n >> k;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::string s;
    std::cin >> s;
    s = "#" + s;
    std::vector<int> L(n + 1, 0), R(n + 2, n + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            L[i] = i;
        }
        else {
            L[i] = L[i - 1];
        }
    }
    for (int i = n; i >= 1; i--) {
        if (s[i] == '1') {
            R[i] = i;
        }
        else {
            R[i] = R[i + 1];
        }
    }
    
    auto pre = work(a, s);
    std::reverse(a.begin() + 1, a.end());
    std::reverse(s.begin() + 1, s.end());
    auto suf = work(a, s);
    std::reverse(a.begin() + 1, a.end());
    std::reverse(s.begin() + 1, s.end());
    std::reverse(suf.begin() + 1, suf.end());
    suf.push_back(0);
    int q = 0;
    std::cin >> q;
    while (q--) {
        int p = 0, v = 0;
        std::cin >> p >> v;
        i64 ans = pre[p] + suf[p] - 2ll * a[p] + 1ll * v;
        if (s[p] == '0') {
            int l = std::max(p + 2 - k, L[p]);
            i64 mn = Inf;
            for (int i = l, j = p + 1; i < p; i++) {
                while (j <= i + k && j <= R[p]) {
                    mn = std::min(mn, suf[j]);
                    j++;
                }
                ans = std::min(ans, pre[i] + mn);
            }
        }
        std::cout << ans << '\n';
    }
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