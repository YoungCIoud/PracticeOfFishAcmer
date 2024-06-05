#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e5, Inf = 1e18;
int c[N + 5];
vector<pair<int,int>> g[N + 5];

int len[N + 5], sum[N + 5], fa[N + 5];
int dfs(int cur, int f)
{
	fa[cur] = f;
	for (auto [to, val] : g[cur])
	{
		if (to == f) continue;
		int num = dfs(to, cur);
		sum[cur] += num;
		len[cur] += len[to] + val * num;
	}
	sum[cur] += c[cur];
	return sum[cur];
}

int res[N + 5];
void dfs(int cur)
{
	for (auto [to, val] : g[cur])
	{
		if (to == fa[cur]) continue;

		res[to] = res[cur] - val * sum[to] + val * (sum[cur] - sum[to]);
		sum[to] = sum[cur];
		dfs(to);
	}
}

signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> c[i];
	}
	for (int i = 1; i < n; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		g[a].push_back({ b, c });
		g[b].push_back({ a, c });
	}

	dfs(1, 0); // 预处理

	res[1] = len[1];
	dfs(1); //  换根dp

	int ans = Inf;
	
	//for (int i = 1; i <= n; i++)
	//{
	//	cout << sum[i] << " \n"[i == n];
	//}
	//for (int i = 1; i <= n; i++)
	//{
	//	cout << len[i] << " \n"[i == n];
	//}

	for (int i = 1; i <= n; i++)
	{
		//cout << res[i] << " \n"[i == n];
		ans = min(ans, res[i]);
	}
	cout << ans << endl;
	return 0;
}
