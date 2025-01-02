#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 998244353;
constexpr int N = 50;
// 枚举每一条边，钦定它为最优路径中最倾斜的边

typedef std::array<int, 2> V; // vector
typedef std::array<int, 2> P; // point

int n;
std::vector<P> p;

// 返回向量 a->b
V vec(P a, P b) {
    return V{ b[0] - a[0], b[1] - a[1] };
}
// 点积
i64 dot(V u, V v) {
    return 1ll * u[0] * v[0] + 1ll * u[1] * v[1];
}
// 叉积
i64 crs(V u, V v) {
    return 1ll * u[0] * v[1] - 1ll * v[0] * u[1];
}
// 向量u不在v的逆时针方向
bool clockwise(V u, V v) {
    return crs(u, v) >= 0 && dot(u, v) >= 0;
}
// 向量u不在v的顺时针方向
bool anti(V u, V v) {
    return crs(u, v) <= 0 && dot(u, v) >= 0;
}

int solve(V base, bool(*chk)(V, V)) {
    std::vector in(n + 1, 0);
    std::vector g(n + 1, std::vector(0, 0));
    for (int i = 0; i <= n; i++) {
        if (!chk(vec(V{ 0, 0 }, p[i]), base)) {
            continue;
        }
        for (int j = 0; j < n; j++) {
            if (i == j || !chk(vec(V{ 0, 0 }, p[j]), base)) {
                continue;
            }
            if (chk(vec(p[i], p[j]), base)) {
                g[i].push_back(j);
                in[j]++;
            }
        }
    }

    std::queue<int> q;
    std::vector f(n + 1, 0);
    q.push(n);
    while (not q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto &to : g[cur]) {
            f[to] = std::max(f[to], f[cur] + 1);
            in[to]--;
            if (in[to] == 0) {
                q.push(to);
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        res = std::max(res, f[i]);
    }
    return res;
}

int main () {
    std::cin >> n;
    p.assign(n, { 0, 0 });
    for (auto &[x, y] : p) {
        std::cin >> x >> y;
    }
	p.push_back({ 0, 0 });

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) {
                continue;
            }

            ans = std::max(ans, solve(vec(p[i], p[j]), clockwise));
            ans = std::max(ans, solve(vec(p[i], p[j]), anti));
        }
    }
    std::cout << ans << '\n';

    system("pause");
    return 0;
}