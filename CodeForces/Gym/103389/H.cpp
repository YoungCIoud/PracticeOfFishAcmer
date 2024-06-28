// 求经过k条边的最短路
#include<iostream>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 500, M = 1e5, Inf = 1e18;
struct
{
	int u, v, w;
}e[M * 2 + 5];
int d[N + 5][N + 5];
int dis[N + 5], backup[N + 5];

signed main()
{
	IOS;
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		e[i * 2] = { a, b, c };
		e[i * 2 - 1] = { b, a, c };
	}

	// BellmanFord
	for (int i = 1; i <= n; i++)
	{
		dis[i] = backup[i] = Inf;
		for (int j = 1; j <= n; j++)
		{
			d[i][j] = Inf;
		}
	}
	dis[1] = 0;
	for (int i = 1; i < n; i++)
	{
		memcpy(backup, dis, sizeof dis);
		//cout << backup[1] << endl;
		for (int j = 1; j <= 2 * m; j++)
		{
			dis[e[j].v] = min(dis[e[j].v], backup[e[j].u] + e[j].w);
		}
		for (int j = 1; j <= n; j++)
		{
			d[i][j] = dis[j];
			//cout << "round:" << i << " " << "dis[" << j << "]=" << dis[j] << endl;
		}
	}

	// solve
	int _t;
	cin >> _t;
	int sum[N + 5] = { 0 };
	while (_t--)
	{
		int t;
		cin >> t;
		for (int i = 1; i < n; i++)
		{
			cin >> sum[i];
			sum[i] += sum[i - 1];
		}
		
		int ans = Inf;
		for (int i = 1; i < n; i++)
		{
			ans = min(ans, d[i][t] + sum[i]);
		}
		cout << ans << endl;
	}

	return 0;
}
