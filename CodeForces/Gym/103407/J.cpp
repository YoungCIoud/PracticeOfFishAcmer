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
constexpr int N = 1e5, M = 1e5, Inf = 1e9;
std::vector<int> d;
std::map<std::pair<int, int>, int> mp;
void init(int c) {
    d.clear();
    mp.clear();
    for (int i = 2; i * i <= c; i++) {
        if (c % i == 0) {
            d.push_back(i);
            while (c % i == 0) {
                c /= i;
            }
        }
    }
    if (c > 1) {
        d.push_back(c);
    }
    return;
}

int f(int a, int c) {
    if (a <= 1) {
        return 0;
    }
    if (c == 1) {
        return a - 1;
    }
    if (mp.count({ a, c })) {
        return mp[{ a, c }];
    }

    int res = a - 1;
    for (auto &p : d) {
        if (c % p != 0) {
            continue;
        }

        int up = (a + p - 1) / p;
        res = std::min(res, f(up, c / p) + up * p - a + 1);
        int low = a / p;
        res = std::min(res, f(low, c / p) + a % p + 1);
    }
    mp[{a, c}] = res;
    return res;
}

void solve()
{
    int a = 0, b = 0;
    std::cin >> a >> b;
    if (a > b) {
        std::swap(a, b);
    }
    init(b - a);

    std::cout << f(a, b - a) << '\n';
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