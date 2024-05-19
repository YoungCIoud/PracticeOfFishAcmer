#include<vector>
#include<iostream>
using namespace std;
const int N = 6e3;
int val[N + 5], fa[N + 5], dp[N + 5][2];
vector<int> g[N + 5];

int max(int a, int b)
{
	return a > b ? a : b;
}

// 0表示不选 1表示选了
void dfs(int cur)
{
	dp[cur][0] = 0, dp[cur][1] = val[cur];
	for (auto to : g[cur])
	{
		dfs(to);
		dp[cur][0] += max(dp[to][1], dp[to][0]);
		dp[cur][1] += dp[to][0];
	}
}

int main()
{
	int n;
	while(cin>>n)
	{
		for (int i = 1; i <= n; i++) 
			cin >> val[i], g[i].clear(), fa[i] = 0;
		for (int i = 1; i <= n; i++)
		{
			int a, b;
			cin >> a >> b;
			g[b].push_back(a);
			fa[a] = b;
		}
		int boss = 1;
		while (fa[boss]) boss = fa[boss];
		dfs(boss);
		cout << max(dp[boss][0], dp[boss][1]) << endl;
	}
	return 0;
}
