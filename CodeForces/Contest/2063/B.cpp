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
    int n = 0, l = 0, r = 0;
    std::cin >> n >> l >> r;
    std::priority_queue<int> ql, qm, qr;
    for (int i = 1; i <= n; i++) {
        int x = 0;
        std::cin >> x;
        if (i < l) {
            ql.push(-x);
        }
        else if (i > r) {
            qr.push(-x);
        }
        else {
            qm.push(-x);
        }
    }

    auto cnt = [&](std::priority_queue<int> u, std::priority_queue<int> v) -> i64 {
        i64 res = 0;
        int num = u.size();
        while (num--) {
            if (v.empty() || u.top() >= v.top()) {
                res += u.top();
                u.pop();
            }
            else {
                res += v.top();
                v.pop();
            }
        }
        return -res;
    };
    std::cout << std::min(cnt(qm, ql), cnt(qm, qr)) << '\n';
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

/*
6
2 1 1
2 1
3 2 3
1 2 3
3 1 3
3 1 2
4 2 3
1 2 2 2
5 2 5
3 3 2 3 5
6 1 3
3 6 6 4 3 2

1
3
6
3
11
8
*/