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
constexpr int N = 2e5, M = 5e5, Inf = 1e9;
std::vector<int> g[N + 5], col(N + 5);
std::vector<std::pair<int, int>> reg; // 区域的大小和最小的编号
std::vector<int> node;
bool vis[N + 5]; // dfs
bool inq[N + 5];

void dfs(int cur, int c, int &cnt) {
    col[cur] = c, cnt++;
    for (auto &to : g[cur]) {
        if (col[to] == 0) {
            dfs (to, c, cnt);
        }
    }
}

void dfs(int cur) {
    vis[cur] = true;
    node.push_back(cur);
    for (auto &to : g[cur]) {
        if (not vis[to]) {
            dfs (to);
        }
    }
}

void solve()
{
    int n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;

    reg.clear();
    node.clear();
    for (int i = 1; i <= n; i++) {
        vis[i] = inq[i] = false;
        g[i].clear();
        col[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }


    for (int i = 1; i <= n; i++) {
        if (col[i] == 0) {
            int cnt = 0;
            dfs(i, i, cnt);
            reg.push_back({ cnt, i });
        }
    }

    std::sort(reg.begin(), reg.end(), [&](const auto &u, const auto &v) {
        if (u.first == v.first) {
            return u.second < v.second;
        }
        else {
            return u.first > v.first;
        }
    });
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    int ans = 0;
    for (int i = 0; i < std::min(k, int(reg.size())); i++) {
        ans += reg[i].first;
        dfs(reg[i].second);
        q.push(reg[i].second);
        inq[reg[i].second] = true;
    }
    std::sort(node.begin(), node.end()); // 在剩余的传送次数用完前，应该按 node 中的顺序输出
    auto it = node.begin();
    k -= reg.size();

    std::cout << ans << '\n';
    while (not q.empty()) {
        int cur = 0;
        if (k > 0) { // 还能传送时
            cur = *it; // 肯定能到达 *it
            if (not inq[*it]) { // 不在队列里就传送
                inq[*it] = true;
                k--;
            }
            else { // 在队列里的话就一定是堆顶
                q.pop();
            }
            it++;
        }
        else { // 没有传送次数就正常取
            cur = q.top();
            q.pop();
        }
        std::cout << cur << ' ';

        for (auto &to : g[cur]) {
            if (not inq[to]) {
                q.push(to);
                inq[to] = true;
            }
        }
    }
    std::cout << '\n';
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