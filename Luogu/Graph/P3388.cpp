// 割点模板题
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr int Mod = 998244353, Inf = 1e9;
constexpr int N = 2e4, M = 1e5;
vct<int> g[N + 5];
int ans;

int dfn[N + 5], low[N + 5], tim;
bool cp[N + 5];
void tarjan(int cur, int fa)
{
	dfn[cur] = low[cur] = ++tim;
	int son = 0;
	for (auto& to : g[cur])
	{
		if (to == fa) continue;

		if (dfn[to] == 0)
		{
			son++;
			tarjan(to, cur);
			low[cur] = std::min(low[cur], low[to]);
			if (cur != fa && dfn[cur] <= low[to])
				cp[cur] = true;
		}
		else
		{
			low[cur] = std::min(low[cur], dfn[to]);
		}
	}
	if (cur == fa && son > 1)
		cp[cur] = true;
}

int main()
{
	int n, m; 
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0) tarjan(i, i);

	for (int i = 1; i <= n; i++)
		if (cp[i]) ans++;
	std::cout << ans << '\n';
	for (int i = 1; i <= n; i++)
		if (cp[i]) std::cout << i << " ";
}
