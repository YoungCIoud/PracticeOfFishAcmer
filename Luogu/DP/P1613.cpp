#include<iostream>
using namespace std;
const int N = 50, Inf = 0x3f3f3f3f;
bool dp[N + 5][N + 5][N];// dp[i][j][k]=1表示有i到j有一条长度为1<<k的路径
int g[N + 5][N + 5];

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] = Inf;
	for (int i = 1; i <= m; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a][b] = 1;
		dp[a][b][0] = true;
	}
	for (int k = 1; k < 32; k++)
		for (int t = 1; t <= n; t++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					dp[i][j][k] |= dp[i][t][k - 1] && dp[t][j][k - 1],
					g[i][j] = dp[i][j][k] ? 1 : g[i][j];
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	cout << g[1][n];
	return 0;
}
