#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N =  3e5;
vector<int> g[N + 5];
int fa[N + 5], SG[N + 5];
void dfs(int cur, int f)
{
	fa[cur] = f;
	for (int i = 0; i < g[cur].size(); i++)
	{
		int to = g[cur][i];
		if (to == f) continue;
		
		dfs(to, cur);
		SG[cur] ^= (SG[to] + 1);
	}
}

bool ans[N + 5];
void dfs(int cur)
{
	ans[cur] = SG[cur];
	for (int i = 0; i < g[cur].size(); i++)
	{
		int to = g[cur][i];
		if (to == fa[cur]) continue;
		
		SG[to] ^= ((SG[cur] ^ (SG[to] + 1)) + 1);
		dfs(to);
	}
}

void solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		g[i].clear();
		SG[i] = 0;
	}
	for (int i = 1; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	dfs(1, 0); // 预处理dfs
	
	dfs(1);
	
	for (int i = 1; i <= n; i++)
	{
		cout << (ans[i] ? 'A' : 'B');
	}
	cout << endl;
	return;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
		solve();
	return 0;
}
