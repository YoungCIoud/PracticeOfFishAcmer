// 构造
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 1e9 + 7, Inf = 1e9;
constexpr int N = 5e5, M = 2e5;

vct<int> g[N + 5];
vct<int> vis(N + 5);

// 找对于根节点来说深度最大的点
ary<int, 2> dfs(int cur, int fa, int depth)
{
	vis[cur] = true;
	ary<int, 2> res = { cur, depth };
	for (auto& to : g[cur])
	{
		if (to == fa)
			continue;

		auto t = dfs(to, cur, depth + 1);
		if (t[1] > res[1])
			res = t;
	}
	return res;
}

void solve()
{
	int n, m;
	std::cin >> n >> m;

	// 特判n = 3
	if (n == 3)
	{
		if (m == 0)
		{
			return void(puts("1 2 3"));
		}
		else if (m == 1)
		{
			int u, v;
			std::cin >> u >> v;
			std::cout << u << " " << 6 - u - v << " " << v << '\n';
			return;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		vis[i] = false;
	
		g[i].clear();
	}

	for (int i = 0; i < m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	// 菊花图无解
	for (int i = 1; i <= n; i++)
		if (g[i].size() == n - 1)
			return void(puts("-1"));

	// 找直径 
	vct<ary<int, 2>> d;
	for (int i = 1; i <= n; i++)
	{
		if (vis[i]) continue;

		ary<int, 2> t;
		t[0] = dfs(i, i, 0)[0];
		t[1] = dfs(t[0], t[0], 0)[0];
		d.push_back(t);
		//std::cout << t[0] << " " << t[1] << '\n';
	}

	// 连直径
	for (int i = 0; i < d.size() - 1; i++)
	{
		int u = d[i][1], v = d[i + 1][0];
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vct<ary<int, 3>> q(n);
	q[0] = { dfs(1, 1, 0)[0], 0, 1};
	int l = 0, r = 1;
	while (l < r)
	{
		auto& [cur, fa, depth] = q[l++];
		//std::cout << cur << " ";
		
		for (auto& to : g[cur])
			if (to != fa)
				q[r++] = { to, cur, depth + 1 };
	}

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < n; j++)
			if ((q[j][2] & 1) == i)
				std::cout << q[j][0] << " ";
	std::cout << '\n';
	return;
}

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
		solve();

	get AC;
}
