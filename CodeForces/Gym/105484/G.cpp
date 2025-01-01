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
std::vector<int> g[N + 5], siz(N + 5);
bool vis[N + 5];
int pa;
void init(int n) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        vis[i] = false;
    }
}

// 找到包括cur在内的那颗树的重心
void find(int cur, int fa, int &gra, int &n) {
    siz[cur] = 1;
    int mx = 0;
    for (auto &to : g[cur]) {
        if (to == fa || vis[to]) {
            continue;
        }

        find(to, cur, gra, n);
        siz[cur] += siz[to];
        mx = std::max(mx, siz[to]);
    }
    // 最后还要考虑以 fa 为根的子树的大小
    mx = std::max(mx, n - siz[cur]);
    if (mx * 2 <= n && gra == 0) {
        gra = cur;
        pa = fa;
    }
}

int ask(int u, int v) {
    std::cout << "? " << u << ' ' << v << std::endl;
    int t = -1;
    std::cin >> t;
    return t;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    init(n);

    for (int i = 1; i <= n; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        if (u != 0) {
            g[i].push_back(u);
            g[u].push_back(i);
        }
        if (v != 0) {
            g[v].push_back(i);
            g[i].push_back(v);
        }
    }

    int ver = 1, gra = 0;
    int ans = 0;
    while (ans == 0) {
        find(ver, 0, gra, n);
        
        std::vector<int> son;
        for (auto &to : g[gra]) {
            if (not vis[to]) {
                son.push_back(to);
            }
        }

        if (son.size() == 0) {
            ans = gra;
        }
        else if (son.size() == 1) {
            ans = ask(son[0], gra) == 0 ? son[0] : gra;
        }
        else {
            siz[pa] = n - siz[gra];
            std::sort(son.begin(), son.end(), [&](int &x, int &y) {
                return siz[x] > siz[y];
            });
            int t = ask(son[0], son[1]);
            if (t == 1) {
                ver = gra;
                vis[son[0]] = true;
                vis[son[1]] = true;
                if (son.size() == 2) {
                    ans = gra;
                }
                else {
                    n = siz[son[2]] + 1;
                }
            }
            else {
                ver = son[t != 0];
                n = siz[son[t != 0]];
                vis[gra] = true;
            }
            gra = 0;
        }
        pa = 0;
    }
    std::cout << "! " << ans << std::endl;
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