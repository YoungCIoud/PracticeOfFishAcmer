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
constexpr int N = 2e5, A = 1e9, K = 2e5, Inf = 1e9;
struct R {
    int l, r;
    int idx;
    int val;

    bool operator< (const R &u) const {
        return val < u.val;
    }
};

void solve()
{
    int n = 0, p = 0, k = 0;
    std::cin >> n >> p >> k;
    std::vector a(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i] %= p;
    }
    std::sort(a.begin(), a.end());
    
    std::priority_queue<R> q;
    for (int l = 0; l < n - 1; l++) {
        int r = std::lower_bound(a.begin(), a.end(), p - a[l]) - a.begin() - 1;
        r = r <= l ? n - 1 : r;
        q.push(R({ l, r, r, (a[l] + a[r]) % p }));
    }
    
    while (k--) {
        if (q.empty()) {
            std::cout << "-1 ";
        }
        else {
            R t = q.top();
            q.pop();
            std::cout << t.val << ' ';
            t.r = t.r - 1 == t.l ? n - 1 : t.r - 1;
            if (t.r != t.idx) {
                t.val = (a[t.l] + a[t.r]) % p;
                q.push(t);
            }
        }
    }
    std::cout << '\n';
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
3
3 10 8
2 4 8
4 6 4
1 2 3 3
5 10 10
1 2 3 4 5
*/