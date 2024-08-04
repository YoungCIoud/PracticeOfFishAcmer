#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 1e9 + 7, Inf = 1e9;
constexpr int N = 1e5, M = 2e5;
vct<int> g[N + 5];

// 求割边
int dfn[N + 5], low[N + 5], tim;
int las[N + 5];
void tarjan(int cur, int fa)
{
	dfn[cur] = low[cur] = ++tim;
	for (auto& to : g[cur])
	{
		if (to == fa) continue;
		if (dfn[to])
		{
			low[cur] = std::min(low[cur], dfn[to]);
		}
		else
		{
			tarjan(to, cur);
			low[cur] = std::min(low[cur], low[to]);
			if (low[to] > dfn[cur]) las[to] = cur;
		}
	}
}

int fa[N + 5];
int getfa(int u)
{
	return u == fa[u] ? u : fa[u] = getfa(fa[u]);
}
bool merge(int u, int v)
{
	int fu = getfa(u), fv = getfa(v);
	fa[fu] = fv;
	return fu != fv;
}

void dfs(int cur, int father, int rt)
{
	//std::cout << rt << ":" << cur << '\n';
	fa[cur] = rt;
	for (auto& to : g[cur])
		if (to != father && fa[to] == to && (las[to] != cur) && (las[cur] != to))
			dfs(to, cur, rt);
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	vct<ary<int, 2>> lun, qie;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		str s;
		std::cin >> u >> v >> s;
		if (s == "Lun")
		{
			lun.push_back({ u, v });

			g[u].push_back(v);
			g[v].push_back(u);
		}
		else
		{
			qie.push_back({ u, v });
		}
	}

	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0) tarjan(i, i);

	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= n; i++)
		if (fa[i] == i) dfs(i, i, i);

	vct<ary<int, 2>> ans;
	for (auto& [u, v] : qie)
		if (merge(u, v))
			ans.push_back({ u, v });
	
	getfa(1);
	for (int i = 2; i <= n; i++)
		if (getfa(i) != fa[1])
		{
			std::cout << "NO\n";
			return 0;
		}
		
	for (auto& [u, v] : lun)
		if ((las[u] != v) && (las[v] != u))
			ans.push_back({ u, v });

	std::cout << "YES\n" << ans.size() << '\n';
	for (auto& [u, v] : ans)
		std::cout << u << " " << v << '\n';

	get AC;
}
