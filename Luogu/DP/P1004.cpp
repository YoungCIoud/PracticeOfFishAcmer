#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 9, Inf = 0x3f3f3f3f;
int g[N + 5][N + 5];
ll dp[N + N + 5][N][N];
// dp[k][i][j]
// 走了k步,且第一条路径的横坐标是i,第二条路径的横坐标是j时的最大值
// 横纵坐标满足x + y - 1 = k(在左上角时看成第一步)
ll trans(int k, int i, int j)
{
	ll res = i == j ? g[i][k + 1 - i] : g[i][k + 1 - i] + g[j][k + 1 - j];
	ll d = max(dp[k - 1][i - 1][j - 1], dp[k - 1][i][j]);
	d = max(d, dp[k - 1][i][j - 1]);
	d = max(d, dp[k - 1][i - 1][j]);
	return res + d;
}
int main()
{
	int n;
	cin >> n;
	int u, v, w;
	while ((cin >> u >> v >> w) && u || v || w)
	{
		g[u][v] = w;
	}
	for (int k = 1; k < 2 * n; k++)
	{
		for (int i = max(1, k - n + 1); i <= min(n, k); i++)
		{
			for (int j = max(1, k - n + 1); j <= min(n, k); j++)
			{
				dp[k][i][j] = trans(k, i, j);
			}
		}
	}
	cout << dp[2 * n - 1][n][n];
	return 0;
}
