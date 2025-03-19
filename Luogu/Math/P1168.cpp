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
int n = 0;
int a[N + 5];
int tr[N + 5], m;

int lowbit(int x) {
    return x & -x;
}
void add(int pos) {
    while (pos <= m) {
        tr[pos]++;
        pos += lowbit(pos);
    }
    return;
}
int sum(int pos) {
    int res = 0;
    while (pos >= 1) {
        res += tr[pos];
        pos -= lowbit(pos);
    }
    return res;
}

void solve()
{
    std::cin >> n;
    std::vector<int> h(1, -1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        h.push_back(a[i]);
    }
    std::sort(h.begin(), h.end());
    h.erase(std::unique(h.begin(), h.end()), h.end());
    m = h.size() - 1;
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(h.begin(), h.end(), a[i]) - h.begin();
    }

    for (int i = 0; i < n; i++) {
        add(a[i]);
        if (i & 1) {
            continue;
        }

        int l = 1, r = m;
        while (l <= r) {
            int mid = l + r >> 1;
            // std::cout << sum(mid) << '\n';
            if (sum(mid) <= (i >> 1)) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        std::cout << h[l] << '\n';
    }
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


    return 0;
}