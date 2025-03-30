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

void solve()
{
    i64 k = 0, b = 0, c = 0, v = 0;
    std::cin >> k >> b >> c >> v;
    i64 ans = 0, l = 0, r = (1ll << 61) / k;
    for (int bit = 61; ~bit; bit--) {
        i64 ll = l, rr = r;
        while (ll <= rr) {
            i64 m = ll + rr >> 1;
            if ((k * m + b) >> bit & 1) {
                rr = m - 1;
            }
            else {
                ll = m + 1;
            }
        }
        std::array<i64, 2> rng[2] = { { l, rr }, { ll, r } };

        int cur = c >> bit & 1;
        if (v >> bit & 1) {
            ans += rng[cur][1] - rng[cur][0] + 1;
            l = rng[cur ^ 1][0];
            r = rng[cur ^ 1][1];
        }
        else {
            l = rng[cur][0];
            r = rng[cur][1];
        }
    }
    std::cout << ans + (r - l + 1) << '\n';
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