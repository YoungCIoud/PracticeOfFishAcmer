#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e5, Inf = 1e18;
vector<pair<int, int>> g[N + 5];
int in[N + 5];
double p[N + 5];
signed main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		g[a].push_back({ b, c });
		in[b]++;
	}
	double ans = 0;
	queue<int> q;
	q.push(1), p[1] = 1;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		double P = p[cur] / g[cur].size();
		for (auto [to, val] : g[cur])
		{
			ans += P * val;
			p[to] += P;

			if (--in[to]) continue;
			q.push(to);
		}
	}
	printf("%.2lf", ans);
	return 0;
}
