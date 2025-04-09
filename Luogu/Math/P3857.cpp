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

constexpr int Mod = 2008;
constexpr int N = 50, L = 50;

i64 p[L];

bool insert(i64 a) {
    for (int bit = L - 1; ~bit; bit--) {
        if (!(a >> bit & 1)) {
            continue;
        }

        if (p[bit]) {
            a ^= p[bit];
        }
        else {
            p[bit] = a;
            return true;
        }
    }
    return false;
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> m >> n;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        i64 a = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'O') {
                a |= (1ll << j);
            }
        }
        if (insert(a)) {
            cnt++;
        }
    }

    std::cout << (1ll << cnt) % Mod << '\n';
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

    sp();

    return 0;
}