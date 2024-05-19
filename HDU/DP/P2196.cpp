#include <cstring>	// memset
#include<vector>
#include<iostream>
using namespace std;
const int N = 1e4;
// [to,val]
vector<pair<int,int>> g[N + 5];
long long dp[N + 5][3];

int max(int x, int y) {
	return x > y ? x : y;
}

void dfs1(int cur)
{
	long long mx=0, fm=0;
	for (auto to : g[cur])
	{
		dfs1(to.first);
		int cos = dp[to.first][0] + to.second;
		if (cos >= mx) fm = mx, mx = cos;
		if (cos > fm && cos < mx) fm = cos;
	}
	dp[cur][0] = mx, dp[cur][1] = fm;
}

void dfs2(int cur)
{
	for (auto to : g[cur])
	{
		// 某个儿子在最长的子树上
		if (dp[to.first][0] + to.second == dp[cur][0])
			dp[to.first][2] = max(dp[cur][2], dp[cur][1]) + to.second;
		else dp[to.first][2] = max(dp[cur][2], dp[cur][0]) + to.second;
		dfs2(to.first);
	}
}

int main()
{
	int n;
	while (~scanf("%d", &n))
	{
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= n; i++) g[i].clear();
		for (int i = 2; i <= n; i++)
		{
			int a, b;
			cin >> a >> b;
			g[a].push_back({ i,b });
		}
		dfs1(1);
		dfs2(1);
		/*for (int i = 1; i <= n; i++)
			cout << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << endl;*/
		for (int i = 1; i <= n; i++)
			cout << max(dp[i][0], dp[i][2]) << endl;
	}
	return 0;
}
