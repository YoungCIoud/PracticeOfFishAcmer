// 按照错误的思路走所做的全是无用功
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 998244353, Inf = 1e18, N = 3e5, M = 1e6;
i64 a[N + 5], dp[N + 5][25], pre[25], suf[25];
vct<int>  g[N + 5];

void dfs(int cur, int fa)
{
	//std::cout << cur << '\n';
	for (int i = 1; i <= 20; i++)
		dp[cur][i] = i * a[cur];

	for (auto& to : g[cur])
	{
		if (to == fa)
			continue;

		dfs(to, cur);
		pre[0] = suf[21] = Inf;
		for (int i = 1; i <= 20; i++)
			pre[i] = std::min(pre[i - 1], dp[to][i]);
		for (int i = 20; i; i--)
			suf[i] = std::min(suf[i + 1], dp[to][i]);
		for (int i = 1; i <= 20; i++)
			dp[cur][i] += std::min(pre[i - 1], suf[i + 1]);
	}
}

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
	{
		int n;
		std::cin >> n;
		for (int i = 1; i <= n; i++)
		{
			std::cin >> a[i];

			g[i].clear();
			for (int j = 0; j < 20; j++)
				dp[i][j] = 0;
		}

		for (int i = 1; i <= n - 1; i++)
		{
			int u, v;
			std::cin >> u >> v;
			g[v].push_back(u), g[u].push_back(v);
		}

		dfs(1, 0);
		std::cout << *std::min_element(dp[1] + 1, dp[1] + 1 + 20) << '\n';
	}

	get AC;
}
