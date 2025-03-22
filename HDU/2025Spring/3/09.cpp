// 并查集
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr int N = 1e6;

int fa[N + 5], pos[N + 5], idx[N + 5], g[N + 5];
int getfa(int u) {
    return u == fa[u] ? u : (fa[u] = getfa(fa[u]));
}
// u <- v;
void merge(int u, int v) {
    fa[getfa(v)] = getfa(u);;
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;

    std::iota(fa + 1, fa + 1 + n, 1);
    std::iota(pos + 1, pos + 1 + n, 1);
    std::iota(idx + 1, idx + 1 + n, 1);
    std::iota(g + 1, g + 1 + n, 1);

    while (q--) {
        int op = 0;
        std::cin >> op;
        if (op == 1) { // 合并到 a 上
            int a = 0, b = 0;
            std::cin >> a >> b;
            merge(pos[a], pos[b]);
        }
        else if (op == 2) { // 移动 a 到部落 b
            int a = 0, b = 0;
            std::cin >> a >> b;
            g[a] = pos[b];
        }
        else if (op == 3) { // 交换 a b 两个部落
            int a = 0, b = 0;
            std::cin >> a >> b;
            std::swap(idx[pos[a]], idx[pos[b]]);
            std::swap(pos[a], pos[b]);
        }
        else { // 找 a 在那个部落
            int a = 0;
            std::cin >> a;
            std::cout << idx[getfa(g[a])] << '\n';
        }
    }
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

    return 0;
}