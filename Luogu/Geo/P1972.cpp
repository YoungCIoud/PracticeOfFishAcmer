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
constexpr int N = 1e6, M = 1e6, MAX = 1e6, Inf = 1e9;

struct {
    int x, y;
    bool isnode;
    int id, co; // the index of a quiry and the coefficient
    
    bool operator< (const auto &u) const {
        if (x == u.x) {
            if (y == u.y) {
                return isnode;
            }
            else {
                return y < u.y;
            }
        }
        else {
            return x < u.x;
        }
    }
} node[N * 3 + 1]; 
int cnt = 0;

void add_node(int x, int y, bool isnode, int id, int co) {
    node[cnt++] = { x, y, isnode, id, co };
}

int tr[MAX + 5];
int lowbit(int u) {
    return u & -u;
}

void add(int pos) {
    if (pos == 0) {
        tr[0]++;
        return;
    }
    while (pos < MAX ) {
        tr[pos] += 1;
        pos += lowbit(pos);
    }
    return;
}

int pre(int pos) {
    int res = tr[0];
    while (pos > 0) {
        res += tr[pos];
        pos -= lowbit(pos);
    }
    return res;
}

int pos[MAX + 5];

void solve() {
    int n = 0; 
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int a = 0;
        std::cin >> a;
        add_node(i, pos[a], true, 0, 0);
        pos[a] = i;
    }

    int m = 0;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        add_node(x - 1, x - 1, false, i, -1);
        add_node(y, x - 1, false, i, 1);
    }
    
    std::sort(node, node + cnt);

    std::vector ans(m, 0);
    for (int i = 0; i < cnt; i++) {
        if (node[i].isnode) {
            add(node[i].y);
        }
        else {
            ans[node[i].id] += node[i].co * pre(node[i].y);
        }
    }
    
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] << '\n';
    }

    return;
}

int main()
{
    IOS;
    int _t = 1;
 //   std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
