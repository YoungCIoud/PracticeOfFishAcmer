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

class BIT {
private:
    int n;
    std::vector<int> tr;

    int lowbit(int x) {
        return x & -x;
    }
    int sum(int pos) {
        int res = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            res += tr[i];
        }
        return res;
    }
public:
    BIT(int _n) {
        n = _n;
        tr.assign(n + 1, 0);
    }

    void add(int pos) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tr[i]++;
        }
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector p(n + 1, 0), pos(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
        pos[p[i]] = i;
    }

    std::vector q(n + 1, std::vector<std::array<int, 3>>());
    for (int i = 0; i < m; i++) {
        int l = 0, r = 0, c = 0;
        std::cin >> l >> r >> c;
        q[p[c]].push_back({ i, l, r });
    }
    
    std::vector ans(m, 0);
    std::vector vis(n + 1, false);
    BIT t(n);
    for (int i = 1; i <= n; i++) {
        for (auto &[id, l, r] : q[i]) {
            ans[id] = l + t.sum(l, r);
        }
        t.add(pos[i]);
    }
    for (auto &i : ans) {
        std::cout << i << '\n';
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

/*
2
5 3
1 4 2 3 5
3 5 4
1 3 2
1 5 4
9 5
1 4 9 2 8 7 3 5 6
1 7 4
2 9 2
3 4 4
5 9 7
1 9 7
*/