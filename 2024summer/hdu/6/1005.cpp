// 一遍过的状压dp
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 500, K = 10;
vct<int> f(1 << (2 * K)), g(59049);

int cnt = 0;
void dfs(int dep, int s, int mx)
{
	if (dep == mx)
	{
		f[s] = cnt;
		g[cnt] = s;
		//printf("%d, %d\n", cnt, s);
		cnt++;
		return;
	}

	dfs(dep + 1, s, mx);
	dfs(dep + 1, s | (1 << (dep * 2)), mx);
	dfs(dep + 1, s | (2 << (dep * 2)), mx);
	return;
}

void solve()
{
	cnt = 0;

	int n, k, m;
	std::cin >> n >> k >> m;
	int status = pow(3, k);
	dfs(0, 0, k);

	vct dp(2, vct<i64>(status, 0));
	vct vis(2, vct<i64>(status, 0));
	dp[0][0] = 1ll;
	vis[0][0] = true;
	for (int i = 1, id = 1; i <= n; i++, id ^= 1)
	{
		str ope;
		std::cin >> ope;

		for (int s = 0; s < status; s++)
		{
			dp[id][s] = dp[id ^ 1][s];
			vis[id][s] = vis[id ^ 1][s];
			int u = 0;

			// g[i]表示第i个状态
			// i = g[f[i]];
			int v = g[s];
			for (int j = 0; j < k; j++, v >>= 2)
			{
				int t = v % 4;
				switch (ope[j])
				{
				case '+':
					t = (t - 1 + 3) % 3;
					break;
				case '-':
					t = (t + 1) % 3;
					break;
				default:
					break;
				}
				u |= (t << (j * 2));
			}
			//std::cout << u << "->" << v << '\n';

			dp[id][s] = (dp[id][s] + dp[id ^ 1][f[u]]) % m;
			vis[id][s] |= vis[id ^ 1][f[u]];
		}
	}

	for (int i = 0; i < status; i++)
	{
		int s = g[i];
		if (vis[n & 1][i])
		{
			for (int j = 0; j < k; j++, s >>= 2)
				std::cout << char('A' + (s & 3));
			std::cout << " " << dp[n & 1][i] << '\n';
		}
	}
	return;
}

int main()
{
	IOS;
	int t = 1;
	std::cin >> t;
	while (t--)
	{
		solve();
	}
	get AC;
}
