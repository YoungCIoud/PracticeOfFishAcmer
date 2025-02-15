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

void solve()
{
    int n = 0;
    i64 k = 0;
    std::cin >> n >> k;
    std::vector<int> pos(n + 1, 0), p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
        pos[p[i]] = i;
    }

    if (k < n) {
        std::cout << -1 << '\n';
        return;
    }

    int lst = 0, x = 0;
    for (int i = n; i >= 1; i--) {
        if (k + 1 >= (i << 1)) {
            k -= i;
        }
        else {
            lst = i;
            x = k - (i - 1);
            break;
        }
    }

    if (x % 2 == 0 && x != 0) {
        p[pos[1]] = lst;
        for (int i = 2, j = 1; i <= lst; i++, j++) {
            i = (i == x ? i + 1 : i);
            j = (j == x ? j + 1 : j);
            p[pos[i]] = j;
        }
    }
    else if (x == 1) {
        p[pos[1]] = lst;
        for (int i = 2; i <= lst; i++) {
            p[pos[i]] = i - 1;
        }
    }
    else if (x == 3) {
        p[pos[1]] = lst == 4 ? 3 : lst;
        p[pos[2]] = 4;
        p[pos[3]] = 1;
        p[pos[4]] = 2;
        if (lst >= 5) {
            p[pos[5]] = 3;
        }
        for (int i = 6, j = 5; i <= lst; i++, j++) {
            p[pos[i]] = j;
        }
    }
    else if (x != 0) {
        p[pos[1]] = lst;
        p[pos[3]] = 1;
        x--;
        for (int i = 4, j = 3; i <= lst; i++, j++) {
            i = (i == x ? i + 1 : i);
            j = (j == x ? j + 1 : j);
            p[pos[i]] = j;
        }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << p[i] << " \n"[i == n];
    }
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