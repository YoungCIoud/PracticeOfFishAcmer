#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    // #define cout cout << ">>>\t"
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

std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

void read(std::array<int, 2> &a) {
    std::cin >> a[0] >> a[1];
}

void solve()
{
    int n = 0;
    std::cin >> n;
    std::array<int, 2> res{};
    int a = 0, b = 0;
    do
    {
        a = 1 + rnd() % n;
        do
        {
            b = 1 + rnd() % n;
        } while (a == b);
        
        std::cout << "? " << n - 2 << ' ';
        for (int i = 1; i <= n; i++) {
            if (i != a && i != b) {
                std::cout << i << ' ';
            }
        }
        std::cout << std::endl;
        read(res);
    } while (res[0] != n / 2 || res[1] != n / 2 + 1);
    
    std::vector<int> p;
    int l = 0, r = 0;
    while (p.size() < 4) {
        l = r + 1;
        while (l == a || l == b) {
            l++;
        }
        r = l + 1;
        while (r == a || r == b) {
            r++;
        }
        std::cout << "? " << 4 << ' ' << a << ' ' << b << ' ' << l << ' ' << r << std::endl;
        read(res);
        if (res[0] == n / 2 && res[1] == n / 2 + 1) {
            std::cout << "! " << l << ' ' << r << std::endl;
            return;
        }
        if (res[0] == n / 2 || res[1] == n / 2 || res[0] == n / 2 + 1 || res[1] == n / 2 + 1) {
            p.push_back(l), p.push_back(r);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            std::cout << "? " << 4 << ' ' << a << ' ' << b << ' ' << p[i] << ' ' << p[j] << std::endl;
            read(res);
            if (res[0] == n / 2 && res[1] == n / 2 + 1) {
                std::cout << "! " << p[i] << ' ' << p[j] << std::endl;
                return;
            }
        }
    }
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