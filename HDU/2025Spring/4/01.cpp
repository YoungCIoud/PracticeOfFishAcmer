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
// constexpr int N = 1e5, M = 1e5, Inf = 1e9;

struct ENEMY {
    int hp, u, idx, cnt;
    bool operator< (const ENEMY &a) const {
        if (hp != a.hp) {
            return hp > a.hp;
        }
        if (u != a.u) {
            return u > a.u;
        }
        return idx > a.idx;
    }
};

void solve()
{
    int n, u, k, hp;
    std::cin >> n >> u >> k >> hp;
    std::priority_queue<ENEMY> attack;
    std::priority_queue<std::pair<int, int>> mx;
    std::vector dead(n + 1, false);
    for (int i = 1; i <= n; i++) {
        ENEMY tmp;
        std::cin >> tmp.u >> tmp.hp;
        tmp.idx = i, tmp.cnt = 0;
        attack.push(tmp);
        mx.push(std::make_pair(tmp.u, i));
    }

    int ans = 0;
    while (hp >= 0 && ans < n) {
        auto cur = attack.top();
        attack.pop();

        cur.hp -= cur.cnt == 0 ? u : (u >> 1);
        cur.cnt++;
        if (cur.hp <= 0) {
            dead[cur.idx] = true;
            ans++;
        }
        else if (cur.cnt < k) {
            attack.push(cur);
        }

        while (not mx.empty() && dead[mx.top().second]) {
            mx.pop();
        }
        if (not mx.empty()) {
            hp -= mx.top().first;
        }
    }
    std::cout << ans << '\n';
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