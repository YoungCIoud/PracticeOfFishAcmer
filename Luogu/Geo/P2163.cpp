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
constexpr int N = 5e5, M = 1e7, Inf = 1e9;

struct {
    int x, y;
    bool tree;
    int id, co; // the index of a quiry and the coefficient
    
    bool operator< (const auto &u) const {
        if (x == u.x) {
            if (y == u.y) {
                return tree;
            }
            else {
                return y < u.y;
            }
        }
        else {
            return x < u.x;
        }
    }
} node[N * 5 + 5]; 
int cnt = 0;

std::vector<int> h;
int hash(int x) {
    return std::lower_bound(h.begin(), h.end(), x) - h.begin();
}

void add_node(int x, int y, bool tree, int id, int co) {
    node[cnt++] = { x, y, tree, id, co };
}

int tr[N * 5 + 5];
int lowbit(int u) {
    return u & -u;
}

void add(int pos) {
    while (pos < h.size()) {
        tr[pos] += 1;
        pos += lowbit(pos);
    }
    return;
}

int pre(int pos) {
    int res = 0;
    while (pos > 0) {
        res += tr[pos];
        pos -= lowbit(pos);
    }
    return res;
}

void solve() {
    h.push_back(-1);
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        x++, y++;
        add_node(x, y, true, 0, 0);
        h.push_back(y);
    }

    for (int i = 0; i < m; i++) {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        std::cin >> x1 >> y1 >> x2 >> y2;
        x1++, y1++, x2++, y2++;
        add_node(x2, y2, false, i, 1);
        add_node(x1 - 1, y1 - 1, false, i, 1);
        add_node(x1 - 1, y2, false, i, -1);
        add_node(x2, y1 - 1, false, i, -1);
        h.push_back(y2), h.push_back(y1 - 1);
    }

    std::sort(h.begin(), h.end());
    h.erase(std::unique(h.begin(), h.end()), h.end());
    
    std::sort(node, node + cnt);
    
    std::vector ans(m, 0);
    for (int i = 0; i < cnt; i++) {
        int y = hash(node[i].y);
        if (node[i].tree) {
            add(y);
        }
        else {
            ans[node[i].id] += node[i].co * pre(y);
        }
    }
    
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] << "\n";
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