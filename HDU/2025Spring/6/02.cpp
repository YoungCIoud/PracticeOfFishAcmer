#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9, L = 20;

int Log[N + 5];

class ST {
private:
    int n;
    std::vector<std::array<i64, L>> a;
public:
    ST() {
        n = -1; // 注意一定要初始化成 -1
        insert(0);
    }
    void insert(i64 val) {
        a.push_back(std::array<i64, L>{});
        a[++n][0] = val;
        for (int l = 1; (1 << l) <= n; l++) {
            a[n][l] = std::max(a[n][l - 1], a[n - (1 << l - 1)][l - 1]);
        }
    }

    i64 ask(int l, int r) {
        int len = Log[r - l + 1];
        return std::max(a[l + (1 << len) - 1][len], a[r][len]);
    }
};

void solve()
{
    int n = 0;
    i64 x = 0;
    std::cin >> n >> x;
    ST st;
    std::vector a(n + 2, 0ll), pre(n + 1, 0ll), suf(n + 2, 0ll);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        st.insert(a[i]);
    }
    for (int i = 2; i <= n; i++) {
        pre[i] = pre[i - 1] + std::abs(a[i] - a[i - 1]);
    }
    for (int i = n - 1; i; i--) {
        suf[i] = suf[i + 1] + std::abs(a[i + 1] - a[i]);
    }
    
    int ans = n;
    for (int L = 1; L <= n; L++) {
        int l = L, r = n;
        while (l <= r) {
            int R = l + r >> 1;
            
            int mx = st.ask(L, R);
            if (pre[L - 1] + suf[R + 1] + std::abs(L - 1 ? mx - a[L - 1] : 0) + std::abs(R + 1 > n ? 0 : mx - a[R + 1]) <= x) {
                r = R - 1;
            }
            else {
                l = R + 1;
            }
        }
        if (l <= n) {
            ans = std::min(ans, l - L + 1);
        }
    }
    
    std::cout << (ans == 1 ? 0 : ans) << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;

    for (int i = 2; i <= N; i++) {
        Log[i] = Log[i >> 1] + 1;
    }

    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}