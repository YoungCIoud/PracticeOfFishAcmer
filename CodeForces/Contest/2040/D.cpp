#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 998244353;
constexpr int N = 2e5;

std::vector<int> g[N + 5];
std::vector<int> res(N + 5);
int num;

void dfs(int cur, int fa) {
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        num++;
        int d = num - res[cur];
        if (d % 2) {
            if (d != 1) {
                num++;
            }
        }
        else if (d == 2) {
            num += 2;
        }
        res[to] = num;
        dfs(to, cur);
    }
}

void solve() {
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    num = 1;
    res[1] = num;
    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        std::cout << res[i] << " \n"[i == n];
    }
    return;
}

int main () {
    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        solve();
    }
    return 0;
}