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

int ask(int l, int r) {
    std::cout << "? " << l << ' ' << r << std::endl;
    int f = 0;
    std::cin >> f;
    return f;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    std::string s;
    for (int l = 1, r = 2; r <= n; r++) {
        int f = ask(l, r);
        if (f != 0) {
            int n1 = r - l - f;
            for (int i = 0; i < n1; i++) {
                s.push_back('1');
            }
            for (int i = n1; i < r - l; i++) {
                s.push_back('0');
            }
            s.push_back('1');
            break;
        }
    }
    if (s.empty()) {
        std::cout << "! IMPOSSIBLE" << std::endl;
        return;
    }
    
    int p0 = s.size() - 1, lst = 1;
    for (int i = p0 + 2; i <= n; i++) {
        int f = ask(p0, i);
        char c = '\000';
        if (f == lst) {
            c = '0';
            lst = 0;
            p0 = i;
        }
        else {
            c = '1';
            lst = f;
        }
        s.push_back(c);
    }
    std::cout << "! " << s << std::endl;
    return;
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