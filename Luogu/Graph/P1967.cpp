#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e4, M = 1e5;
int fa[N * 2 + 5], cnt = 0;
int val[N + 5];
int getfa(int u) {
	return fa[u] == u ? u : (fa[u] = getfa(fa[u]));
}

int st[N * 2 + 5][25], dep[N * 2 + 5];
std::vector<int> g[N * 2 + 5];
void dfs(int cur, int deep = 1) {
	dep[cur] = deep;
	for (auto &to : g[cur]) {
		dfs(to, deep + 1);
		st[to][0] = cur;
	}
}

typedef std::array<int, 3> edge;
void solve()
{
	int n = 0, m = 0;
	std::cin >> n >> m;
	std::vector e(m, edge{});
	for (auto &[u, v, w] : e) {
		std::cin >> u >> v >> w;
	}
	std::sort(e.begin(), e.end(), [](edge u, edge v){
		return u[2] > v[2];
	});

	for (int i = 1; i <= n + n; i++) {
		fa[i] = i;
		g[i].clear();
	}
	for (auto &[u, v, w] : e) {
		int fu = getfa(u);
		int fv = getfa(v);
		if (fu == fv) {
			continue;
		}

		cnt++;
		val[cnt] = w;
		g[n + cnt].push_back(fu);
		g[n + cnt].push_back(fv);
		fa[fu] = fa[fv] = n + cnt;
	}
	for (int i = 1; i <= cnt; i++) {
		if (fa[i + n] == i + n) {
			dfs(i + n);
		}
	}

	for (int l = 1; l <= 24; l++) {
		for (int i = 1; i + (1 << l) <= n + cnt; i++) {
			st[i][l] = st[st[i][l - 1]][l - 1];
		}
	}

	int q = 0;
	std::cin >> q;
	while (q--) {
		int u = 0, v = 0;
		std::cin >> u >> v;

		if (getfa(u) != getfa(v)) {
			std::cout << -1 << '\n';
			continue;
		}

		if (dep[u] < dep[v]) {
			std::swap(u, v);
		}
		if (dep[u] != dep[v]) {
			for (int l = 24; l >= 0; l--) {
				if (dep[st[u][l]] >= dep[v]) {
					u = st[u][l];
				}
			}
		}
		for (int l = 24; l >= 0; l--) {
			if (st[u][l] != st[v][l]) {
				u = st[u][l];
				v = st[v][l];
			}
		}
		std::cout << val[st[u][0] - n] << '\n';
	}
}

int main()
{
	// IOS;
	int t = 1;
	// std::cin >> t;
	
	while (t--)
	{
		solve();
	}

	system("pause");

	return 0;
}