#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e5, M = 1e5, Inf = 1e16, Mod = 1e9 + 7;
int n;
vector<int> g[N + 5];
int siz[N + 5], f[N + 5];

bool flag = false;
void dfs(int cur, int fa)
{
	siz[cur] = 1, f[cur] = fa;
	for (auto to : g[cur])
	{
		if (to == fa) continue;
		dfs(to, cur);
		siz[cur] += siz[to];
	}
}
signed main()
{
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, 0);
	int cur = n, cnt = -1;
	while (f[cur])
	{
		cnt++;
		cur = f[cur];
	}
	cur = n;
	for (int i = 1; i <= cnt / 2; i++, cur = f[cur]);
	//cout << cur << endl;
	int cntn = siz[cur];
	int cnt1 = siz[1] - siz[cur];
	puts(cnt1 <= cntn ? "Snuke" : "Fennec");
	return 0;
}
