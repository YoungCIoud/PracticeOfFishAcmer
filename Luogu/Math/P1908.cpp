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
constexpr int N = 5e5;

int tot;
int tr[N + 5];

int lowbit(int x) {
    return x & -x;
}

void add(int pos) {
    while (pos <= tot) {
        tr[pos]++;
        pos += lowbit(pos);
    }
    return;
}

int ask(int pos) {
    int res = 0;
    while (pos > 0) {
        res += tr[pos];
        pos -= lowbit(pos);
    }
    return res;
}

void solve() {
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0), h(1, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        h.push_back(a[i]);
    }

    std::sort(h.begin(), h.end());
    h.erase(std::unique(h.begin(), h.end()), h.end());
    tot = h.size() -  1;

    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(h.begin(), h.end(), a[i]) - h.begin();
    }

    i64 ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        add(a[i]);
        ans += ask(a[i] - 1);
    }

    std::cout << ans << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
//    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}